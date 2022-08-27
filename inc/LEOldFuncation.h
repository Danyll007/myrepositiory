#pragma once
#ifdef CONFOCAL_DLL
#else
#define CONFOCAL_DLL extern "C" _declspec(dllimport)
#endif
/********************新版本DLL不再推荐使用函数，以下函数为旧版本DLL函数接口，新版本DLL兼容以下
函数，客户新开发程序推荐使用新的替代函数******************************************************/
/*
函数功能：获取控制器指定通道量程，单位为μm,建议使用LE_GetDistanceRangeLimit代替。
参数：
dRange-[out]保存获取到的量程值，量程范围为0~dRange。
specHandle-[in]控制器句柄。
channel-[in]通道序号，当前默认为1。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_GetDistanceRange(float &dRange, int specHandle, int channel = 1);
/*
函数功能：[只能在控制器空闲状态下调用]开启指定通道采集指定数量的高度测量结果任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValues(double *pRstHigh, int pts, int specHandle, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]开启指定通道采集指定数量的高度测量结果、波形数据任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesIntensity(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa, int channel = 1);

/*
函数功能：获取指定数量的测量结果、感光度、峰像素位置数据。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave-[out]pts个点波峰像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesPeakWave(double *pRstHigh, int pts, int specHandle, float *pUnitRa, float *pPeakWave, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]获取指定数量的测量结果、波形曲线、感光度、峰像素位置数据。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave-[out]pts个点像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesIntensityPeakWave(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa,
	float *pPeakWave, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]开启指定通道采集指定数量的高度测量结果任务,同时需要给定回
调函数指针，当采集任务完成或者被用户主动停止后，DLL内部将执行给定回调函数。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesEx(double *pRstHigh, int pts, int specHandle, CBCaptureComplete pFunction, int executeMode = 0, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]开启指定通道采集指定数量的高度测量结果、能量曲线数据、感光
度数据任务，当采集任务完成或者被用户主动停止后，DLL内部将执行给定回调函数。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesIntensityEx(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa,
	CBCaptureComplete pFunction, int executeMode = 0, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]获取指定数量的测量结果、感光度、峰像素位置数据,当采集任务
完成或者被用户主动停止后，DLL内部将执行给定回调函数。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesPeakWaveEx(double *pRstHigh, int pts, int specHandle, float *pUnitRa, float *pPeakWave,
	CBCaptureComplete pFunction, int executeMode = 0, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]获取指定数量的测量结果、波形曲线、感光度、峰像素位置数据，
当采集任务完成或者被用户主动停止后，DLL内部将执行给定回调函数。
*/
CONFOCAL_DLL int __stdcall LE_StartGetValuesIntensityPeakWaveEx(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa,
	float *pPeakWave, CBCaptureComplete pFunction, int executeMode = 0, int channel = 1);

/********以下为旧版本函数不推荐使用，适用于单通道采集与多通道采集，当使用多通道采集时，可以通过
下列函数设置需要获取的数据类型及保存的位置，然后通过LE_StartGetChannelsValues函数来同
步启用多个通道的采集任务*********/
/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道高度数据采集相关参数，但不开启采集任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetValuesParam(double *pRstHigh, int pts, int specHandle, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道高度数据、波形曲线数据、及感光度等数据采
集相关参数，但不开启采集任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetValuesIntensityParam(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道高度数据、波形曲线数据、感光度、像素位置
数据采集相关参数，但不开启采集任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave-[out]pts个点波峰像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetValuesIntensityPeakWaveParam(double *pRstHigh, int pts, int specHandle, int *pPrdItn, float *pUnitRa,
	float *pPeakWave, int channel = 1);


/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道高度数据、波形曲线数据、感光度、像素位置
数据采集相关参数，但不开启采集任务。
参数：
pRstHigh-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集高度点数。
specHandle-[in]控制器句柄。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave-[out]pts个点波峰像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetValuesPeakWaveParam(double *pRstHigh, int pts, int specHandle, float *pUnitRa, float *pPeakWave, int channel = 1);

/*************************旧版本单边测厚数据获取相关函数************************/
/*
函数功能：[只能在控制器空闲状态下调用]设置指定通道厚度数据采集相关参数，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessParam(double *pRstTK, int pts, int specHandle, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定通道厚度数据、波形曲线数据、及感光度等数据采集相关
参数，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
channel-[in]通道序号。
返回值：
1-开始采集指令成功。
-1当前设备上一次采集任务尚未完成。
其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessItnParam(double *pRstTK, int pts, int specHandle, int *pPrdItn, float *pUnitRa, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道厚度数据、上下表面等高度数据采集相关参数
，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pDistance1-[out]保存采集到的上表面高度数组。
pDistance2-[out]保存采集到的下表面高度数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
channel-[in]通道序号。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessDTParam(double *pRstTK, double *pDistance1, double *pDistance2, int pts, int specHandle, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道厚度数据、上下表面高度数据、波形曲线数据
、及感光度等数据采集相关参数，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pDistance1-[out]保存采集到的上表面高度数组。
pDistance2-[out]保存采集到的下表面高度数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个单位像素能量数组，数组长度为pts。
channel-[in]通道序号。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessDTItnParam(double *pRstTK, double *pDistance1, double *pDistance2, int pts, int specHandle, int *pPrdItn,
	float *pUnitRa, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道厚度数据、上下表面高度数据、波形曲线数据
、感光度、像素位置数据采集相关参数，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pDistance1-[out]保存采集到的上表面高度数组。
pDistance2-[out]保存采集到的下表面高度数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
pPrdItn-[out]pts个点波形数据指针，数组长度为pts*length（length代表单帧光谱的长度，可以通过
LE_GetChannelIntensityMsg函数获得）。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave1-[out]保存上表面波峰像素位置数组，数组长度为pts。
pPeakWave2-[out]保存下表面波峰像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessDTItnPeakWaveParam(double *pRstTK, double *pDistance1, double *pDistance2, int pts, int specHandle,
	int *pPrdItn, float *pUnitRa, float *pPeakWave1, float *pPeakWave2, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]设置指定控制器通道厚度数据、上下表面高度数据、波形曲线数据
、感光度、波峰像素位置数据采集相关参数，但不开启采集任务。
参数：
pRstTK-[out]保存采集到的测量结果数据数组。
pDistance1-[out]保存采集到的上表面高度数组。
pDistance2-[out]保存采集到的下表面高度数组。
pts-[in]期望采集测量结果数量。
specHandle-[in]控制器句柄。
pUnitRa-[out]pts个点感光度数组，数组长度为pts。
pPeakWave1-[out]保存上表面波峰像素位置数组，数组长度为pts。
pPeakWave2-[out]保存下表面波峰像素位置数组，数组长度为pts。
channel-[in]通道序号。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetChannelGetThicknessDTPeakWaveParam(double *pRstTK, double *pDistance1, double *pDistance2, int pts,
	int specHandle, float *pUnitRa, float *pPeakWave1, float *pPeakWave2, int channel = 1);

/*
函数功能：[只能在控制器空闲状态下调用]获取指定控制器一个或多个通道的高度测量结果,函数执行后控制
器才开始采集数据，采集完成后函数才返回执行状态，并且结果值存储在pValue中，注意此函数每一个通道只
能获取一个高度结果，支持获取多个通道，例如channels的值为2时，函数执行完后pValue保存2个高度结果，
分别为已启用的第一个通道和第二个通道的高度结果，推荐使用LE_GetSingleValueRTEx替代。
参数：
pValue-[out]保存获取到的测量结果，如果需要获取多个通道结果时，所有结果按通道顺序依次保存。
specHandle-[in]控制器句柄。
channels-[in]需获取结果值的通道数量，例如该参数为1时表示获取第一个通道的结果值，该参数为2时表示
获取已启用通道的第一、第二两个通道的结果值，依此类推。
data0-[in]预留参数。
data1-[in]预留参数。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_GetSingleValueRT(double *pValue, int specHandle, int channels = 1, int data0 = 0, int data1 = 0);
/*
函数功能：[只能在控制器空闲状态下调用]获取指定控制器一个或多个通道的厚度测量结果,函数执行后控制
器才开始采集数据，采集完成后函数才返回执行状态，并且结果值存储在pTKValue、pDistance1、pDistance2
中，注意此函数每一个通道只能获取tkCount个结果，支持获取多个通道，例如channels的值为2，tkCount值
为1时，函数执行完后pTKValue保存2*1个厚度结果，分别为已启用的第一个通道的第一层厚度和第二个通道的
第一层厚度结果，同理pDistance1、pDistance2存储情况也是一样推荐使用LE_GetSingleTKValueRTEx替代。
参数：
pTKValue-[out]获取到的厚度测量结果，该数组长度需大于等于tkCount*channels。
tkCount-[in]期望获取的层数。
specHandle-[in]控制器句柄。
channels-[in]需获取结果值的通道数量，例如该参数为1时表示获取第一个通道的结果值，该参数为2时表示
获取已启用通道的第一、第二两个通道的结果值，依此类推。
pDistance1-[out]获取到的每一层上表面测量结果，该数组长度需大于等于tkCount*channels，如果不需要该
值则参数输入0或空指针，假设tkCount=2，channels=2，则第二个通道的上表面测量结果存储的起始地址为
pDistance1[1*tkCount]。
pDistance2-[out]获取到的每一层下表面测量结果，该数组长度需大于等于tkCount*channels，如果不需要该
值则参数输入0或空指针,内部存储顺序与pDistance1相同。
data0-[in]预留参数。
data1-[in]预留参数。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_GetSingleTKValueRT(double *pTKValue, int tkCount, int specHandle, int channels = 1,
	double *pDistance1 = 0, double *pDistance2 = 0, int data0 = 0, int data1 = 0);

/*
函数功能：设置指定控制器外触发模式下分频触发比例,注意该功能需控制器本身支持该功能才可使用!
参数：
specHandle-[in]控制器句柄。
counterVal-[in]分频比例，默认为1，例如想每5个外部触发信号使控制器采集一帧数据，则该参数设为5。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetFractionalFrequency(int specHandle, int counterVal = 1);

/*
函数功能：获取指定控制器外触发模式下分频触发比例,注意该功能需控制器本身支持该功能才可使用!
参数：
specHandle-[in]控制器句柄。
返回值：
非零-获取到当前控制器分频比例。
-36-控制器句柄无效或不存在。
*/
CONFOCAL_DLL int __stdcall LE_GetFractionalFrequency(int specHandle);

/*
函数功能：清除指定控制器外触发模式下分频计数，例如设置分频比例为5时，已发送了3个触发信号时，希望
控制器对触发信号重新计数时可调用该函数,注意该功能需控制器本身支持该功能才可使用!
参数：
specHandle-[in]控制器句柄。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_ClearFractionalCountesy(int specHandle);

/**********************************新版本废弃函数，只保留接口以便兼容旧版本DLL,函数执行将不做任
何操作，若之前有使用到可直接删除相关代码******************************************************/
/*
函数功能：设置通道光斑中心位置,及单个通道光斑所占行数,当前函数于20190701已停止使用。
输入参数：
offsetLine-[in]待设置光斑中心位置。
lines-[in]光斑所占行数。
specHandle-[in]待设置控制器句柄。
channel-[in]通道序号。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetPosOffset(int offsetLine, int lines, int specHandle, int channel);

/*
函数功能：采集控制器指定通道dark数据，采集前请先用黑色盖子盖住对应通道探头，直到采集完成，当前函
数已于20170701停止使用，请使用LE_CaptureChannelsIntensityCaliData函数进行dark操作。
参数：
specHandle-[in]控制器句柄。
channel-[in]通道序号。
返回值：-16-指定功能不支持。
备注：20190509废除，即使调用也不启任何作用！！！
*/
CONFOCAL_DLL int __stdcall LE_CaptureIntensityCaliData(int specHandle, int channel = 1);
/*
函数功能：获取控制器指定通道调试数据是否导出开关,旧版函数，只保留接口，函数调用不起任何作用。
参数：
exportSta-[out]保存获取到的状态值，0-不导出，1-导出。
specHandle-[in]控制器句柄。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_GetDebugDataExportState(int &exportSta, int specHandle);

/*
函数功能：设置控制器指定通道调试数据是否导出开关,旧版函数，只保留接口，函数调用不起任何作用。
参数：
exportSta-[in]保存获取到的状态值，0-不导出，1-导出，默认为0。
specHandle-[in]控制器句柄。
返回值：成功返回1，其他返回值请参考返回值定义表。
*/
CONFOCAL_DLL int __stdcall LE_SetDebugDataExportState(int exportSta, int specHandle);

/*
函数功能：开启或关闭DLL内部自动调节曝光、增益功能。
参数：
bAuto-[in]true开启自动调节功能,false关闭自动调节功能。
specHandle-[in]控制器句柄。
返回值：1-设置成功；其他返回值请参照返回值定义表。
备注：20200918废除，即使调用也不启任何作用！！！
*/
CONFOCAL_DLL int __stdcall LE_SetAutoEptGain(bool bAuto, int specHandle);

/*
函数功能：获取DLL内部自动调节曝光、增益功能状态。
参数：
bAuto-[out]保存获取到的自动调节功能状态。
specHandle-[in]控制器句柄。
返回值：1-获取成功；其他返回值请参照返回值定义表。
备注：20200918废除，即使调用也不启任何作用！！！
*/
CONFOCAL_DLL int __stdcall LE_GetAutoEptGainSta(bool &bAuto, int specHandle);

/*
函数功能：[只能在控制器空闲状态下调用]通过文件载入单通道配置数据,LE_LoadDeviceConfigureFromFile
函数调用后已载入所有通道参数，当前函数仅在某通道参数修改乱了之后需重新加载文件内参数使用，一般无
需使用。
参数：
filePath-[in]目标文件路径字符数组，允许最大长度2000，路径末尾必须有空字符（即ASCII码为0的字符）
结尾，文件格式为.dcfg。
specHandle-[in]控制器句柄。
channel-[in]通道序号。
pFiberSN-[in]光纤序列号，目前默认为空，调用函数时无需输入参数。
pLensSN-[in]探头序列号，目前默认为空，调用时无需输入参数。
返回值：成功返回1，其他返回值请参考返回值定义表。
备注：20210110废除。
*/
CONFOCAL_DLL int  __stdcall LE_LoadChannelConfigureFromFile(wchar_t *filePath, int specHandle, int channel = 1, wchar_t *pFiberSN = 0, wchar_t *pLensSN = 0);
