/***	File:			SampleFilterMain.h****	Description:	Header file for utility routines contained in SampleFilterMain.****	Version:		1.0****	Copyright 1999 Apple Computer. All rights reserved.****	You may incorporate this sample code into your applications without**	restriction, though the sample code has been provided "AS IS" and the**	responsibility for its operation is 100% yours.  However, what you are**	not permitted to do is to redistribute the source as "ABC Sample Code"**	after having made changes. If you're going to re-distribute the source,**	we require that you make it clear in the source that the code was**	descended from Apple Sample Code, but that you've made changes.***/OSStatus setText(DialogPtr dp, short item, ConstStr255Param text);OSStatus getText(DialogPtr dp, short item, Byte *text);short setControl(DialogPtr dp, short item, short value);void setRadio(DialogPtr dp, short first, short last, short which);short getControl(DialogPtr dialog, short item);