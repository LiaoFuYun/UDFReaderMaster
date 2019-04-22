/*
 * This file is part of libudfread
 * Copyright (C) 2014-2015 VLC authors and VideoLAN
 *
 * Authors: Petri Hintukainen <phintuka@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "udfread.h"
#include "log.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <jni.h>
#include <string.h>


static int _cat(UDFFILE *fp, FILE *out, int64_t clipLength) {
    uint8_t buf[2048];
    int64_t got = 0;
    ssize_t result;

    // 截取第一个片段10M保存
    while ((result = udfread_file_read(fp, buf, sizeof(buf))) > 0 && got <= clipLength) {
        fwrite(buf, 1, (size_t) result, out);
        got += result;
    }

    if (result < 0) {
        LOGE("udfread_file_read(offset=%"PRId64") failed\n", udfread_file_tell(fp));
        return -1;
    }
    LOGD("wrote %"PRId64" bytes of %"PRId64"\n", got, udfread_file_size(fp));
    if(got <= 0){
        return -1;
    }
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_lfy_udfreader_UDFReader_getClipSample(JNIEnv *env, jobject obj,
                                                                      jstring isoPath,
                                                                      jstring firstClipPath,
                                                                      jstring sampleSavePath,
                                                                      jint clipLength) {
    udfread *udf;
    UDFFILE *fp;
    udf = udfread_init();
    if (!udf) {
        LOGI("udfread_init() failed\n");
        return -1;
    }
    const char *isoPathChar = (*env)->GetStringUTFChars(env, isoPath, 0);
    LOGI("imgPath: %s", isoPathChar);
    if (udfread_open(udf, isoPathChar) < 0) {
        LOGI("udfread_open(%s) failed\n", isoPathChar);
        udfread_close(udf);
        return -1;
    }
    const char *firstClipPathChar = (*env)->GetStringUTFChars(env, firstClipPath, 0);
    LOGI("firstClip: %s", firstClipPathChar);
    fp = udfread_file_open(udf, firstClipPathChar);
    if (!fp) {
        LOGD("udfread_file_open(%s) failed\n", firstClipPathChar);
        udfread_close(udf);
        return -1;
    }

    FILE *out;
    const char *outFilePath = (*env)->GetStringUTFChars(env, sampleSavePath, 0);
    if ((out = fopen(outFilePath, "w+")) == 0) {
        LOGE("dest file open failed! ");
        return -1;
    }
    int result = _cat(fp, out, clipLength);
    fclose(out);
    udfread_file_close(fp);
    udfread_close(udf);
    return result;
}

