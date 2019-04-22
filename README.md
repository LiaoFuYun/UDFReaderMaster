# UDFReaderMaster
无需挂载，截取蓝光ISO片段样本，通过读取样本的形式获得蓝光ISO音视频编码信息

```
    /**
     * 截取蓝光iso片段样本，通过样本获取音视频编码信息，可免去iso挂载步骤
     *
     * @param isoPath        蓝光iso文件路径
     * @param firstClipPath  要截取的片段路径(/BDMV/STREAM/ + 片段名) e.g. /BDMV/STREAM/00001.m2ts
     * @param sampleSavePath 截取后的片段文件保存路径
     * @param clipLength     截取长度 e.g. 10 * 1024 * 1024 = 10M
     * @return 0 成功
     */
    private native int getClipSample(String isoPath, String firstClipPath, String sampleSavePath, int clipLength);
```
