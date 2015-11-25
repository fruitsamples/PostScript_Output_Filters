/**	@name PSStreams.h*/	/**		@name Introduction		This file contains types and defines needed for using streams and stream routines		built into PSUtilsLib.	*//*	File:		PSStreams.h	Contains:	This file contains types and defines needed for using streams and stream routines				built into PSUtilsLib.  	Version:	Technology:	PrintingLib 8.7 				Release:	1.1 	Copyright:	� 1996-1999 by Apple Computer Inc. All Rights Reserved. 	Bugs?:		For bug reports, consult the following page on 				the World Wide Web:  					http://developer.apple.com/bugreporter/*/#ifndef __PSSTREAMS__#define __PSSTREAMS__#ifndef __FILES__#include <Files.h>#endif#ifndef __COLLECTIONS__#include <Collections.h>#endif#ifndef __PSSECTIONINFO__#include "PSSectionInfo.h"#endif#if PRAGMA_ONCE#pragma once#endif#ifdef __cplusplusextern "C" {#endif#if PRAGMA_IMPORT#pragma import on#endif#if PRAGMA_STRUCT_ALIGN	#pragma options align=mac68k#elif PRAGMA_STRUCT_PACKPUSH	#pragma pack(push, 2)#elif PRAGMA_STRUCT_PACK	#pragma pack(2)#endif/**	@name PSStreams Defines*/		/**		#FLUSHWRITE# is used as an 'nBytes' value. 				#FLUSHWRITE# is used as an 'nBytes' value when using a stream write routine in order		to get the data flushed to the destination. 	*/	#define FLUSHWRITE	-1L							/**		#psOutConst# is a macro used to emit a constant string into the StreamInfoData 'comm'. 				psOutConst is a macro used to emit a constant, #C# string into the		StreamInfoData 'comm'.	*/	#define psOutConst(comm, s)	 psOutBlock((comm), (s), sizeof(s)-1)				/****** Enums and Typedefs ******//**	@name PSStreams Enums and Typedefs*/		/**		@name PSStreamType 				The types of PSStreams recognized by the streams code built into PSUtilsLib and		its various clients. 				At the current time, only the types kPSSerialStream and kPSRandomAccessStream are relevant		to 3'rd party developers.	*/ 			/** PSStreamType */ 	enum PSStreamType{		/// ReservedStream Type1 		kReservedStreamType1 = 	0,			/// ReservedStream Type2 		kReservedStreamType2 = 	1,			/// ReservedStream Type3 - equivalent to old kPSPrintStream  		kReservedStreamType3 = 	2,			/// PSSerialStream - Use to get the PostScript stream.			kPSSerialStream = 		3,		/// PSRandomAccessStream - Use to PS read file data				kPSRandomAccessStream = 4,			/// Use when spooling but don't want to write spool file // DMG411		kPSNullSpoolStream = 131,				/// UCHAR_MAX		kPSStreamTypeMaxValue = UCHAR_MAX		};	typedef enum PSStreamType PSStreamType;	/*	The PSWriteProc is called to emit some PostScript into the stream. 	'psStream' is the current stream.  'data' points to a buffer of 'nBytes'	worth of new PostScript. The PSWriteProc must consume	the data completely before returning.		PSWriteProc can return an error to cause the caller to abort.*/ 	typedef OSStatus (*PSWriteProc)(struct PSStream *psStream, const void *data, SInt32 nBytes);		/*	The PSReadProc is called to see if any data has come back on the	back channel. 'psStream' is the current stream. 'data' points to a memory	block that can hold *'nBytes' bytes of data. On return, PSReadProc copies	at most *'nBytes' worth of bytes to 'data' and then sets *'nBytes' to	the number of bytes placed into 'data'. 			PSReadProc can return an error which should call the caller	to abort.*/	typedef OSStatus (*PSReadProc)(struct PSStream *psStream, void *data, SInt32 *nBytes);				/**	@name PSSerialStream 		A low level converter is passed a PSSerialStream to write the converted data.*/	/** PSSerialStream */    struct PSSerialStream{		/// write		PSWriteProc write;		/// read		PSReadProc read;		/// reserved		UInt32		reserved;		/// pos		PSPosition pos;					};	typedef struct PSSerialStream PSSerialStream;/*	PSGetEOFProc is used to obtain the total size of a stream which has	a known 'length'. In particular it is used for streams which represent a file.*/	typedef OSStatus (*PSGetEOFProc)(struct PSStream *psStream, SInt32 *streamSize);/*	PSGetPosProc is used to obtain the current position within a stream which can be	randomly accessed. In particular it is used for streams which represent a file.*/	typedef OSStatus (*PSGetPosProc)(struct PSStream *psStream, SInt32 *currentPos);/*	PSSetPosProc is used to set the current position within a stream which can be randomly	accessed. In particular it is used for streams which represent a file. 		The	positionMode parameter can have the values fsFromStart, fsFromLEOF, and, fsFromMark;	just as with the file system calls. The offset parameter is the distance to move	the mark from the beginning (fsFromStart), end (fsFromLEOF), or current 	position (fsFromMark).*/		typedef OSStatus (*PSSetPosProc)(struct PSStream *psStream, SInt32 positionMode, SInt32 offset);/**	@name PSRandomAccessStream	A low level converter is passed a PSRandomAccessStream to write the converted data.*/	/** PSRandomAccessStream */    struct PSRandomAccessStream{		/// serialStream		PSSerialStream serialStream;		/// getPos		PSGetPosProc getPos;		/// setPos		PSSetPosProc setPos;		/// getEOF		PSGetEOFProc getEOF;				};	typedef struct PSRandomAccessStream PSRandomAccessStream;/**	@name PSReservedStreamType1		PSReservedStreamType1 - more info needed*/	/** PSReservedStreamType1 */    struct PSReservedStreamType1{		/// null		short null;	};	typedef struct PSReservedStreamType1 PSReservedStreamType1;/**	@name PSReservedStreamType2		PSReservedStreamType2 - more info needed*/	/** PSReservedStreamType2 */    struct PSReservedStreamType2{		/// dataFRef		short dataFRef;		/// resFRef		short resFRef;	};	typedef struct PSReservedStreamType2 PSReservedStreamType2;/**	@name PSNullSpoolStream		PSNullSpoolStream - more info needed*/	/** PSNullSpoolStream */ 	struct PSNullSpoolStream{		/// null		short null;	};	typedef struct PSNullSpoolStream PSNullSpoolStream;/**	@name PSStream		The general PSStream structure specifies the type of stream followed	by the data describing the stream*/	/** PSStream */	struct PSStream{		/// The type of Stream, used to pick from the union below.		PSStreamType type;					/// Reserved to a Streams Implementation and is not to be used by the user of the stream 		void *reserved;							union{				/// PSReservedStream Type1				PSReservedStreamType1 null;						/// PSReservedStream Type2				PSReservedStreamType2 spool;					/// PSSerialStream				PSSerialStream ps;								/// PSRandomAccessStream				PSRandomAccessStream file;						/// PSNullSpoolStream				PSNullSpoolStream nullSpool;				}u;		};		typedef struct PSStream PSStream;/* UpdateStatusProc */	typedef OSStatus (*UpdateStatusProc)(void *refcon, StringPtr statusStr, Boolean *updated, Boolean connOpen, Boolean deadTime);/* SectionStatusProc */	typedef OSStatus (*SectionStatusProc)(PSStream *stream, void *refcon, struct PSPosition *psPos);/**	@name StatusProcs	This structure specifies the status output routine callbacks the caller wishes to have called by	the streams code.*/	/** StatusProcs */    struct StatusProcs{		/// refcon		void *refcon;		/// updateStatus		UpdateStatusProc		updateStatus;		/// sectionStatus		SectionStatusProc		sectionStatus;	};	typedef struct StatusProcs StatusProcs;/* clientDataProc */	typedef OSStatus (*clientDataProc)(PSStream *psStream, const void *data, SInt32 nBytes, void *refcon);/**	@name SubsectionStr		The SubsectionStr structure provides both a format string and a subsection value	to an output routine.*/	/** SubsectionStr */    struct SubsectionStr{		/// format		StringPtr format;		/// subsection		PSSubsection subsection;	};	typedef struct SubsectionStr SubsectionStr;/**	@name StreamInfoData		Allocated by #psSetupStreamInfoData()#. */	/** StreamInfoData */	typedef struct StreamInfo *StreamInfoData;	/****** ProtoTypes ******//**	@name PSStreams Prototypes*/			/**		Allocates and initializes a #StreamInfoData# structure and returns it 		in *comm so that it can be used	by the other formatting routines. 			The #StreamInfoData# structure is allocated and setup so that it points to the stream #psStream#. 			Communications settings such as 8 bit and control character usage are taken from #hints#.				@param	comm	a pointer to a #StreamInfoData# structure which holds the newly						created #StreamInfoData# structure.				@param	psStream	a pointer to a #PSStream# structure pointed to by #comm#.				@param hints	a #Collection# which contains settings to be used by #psStream#.				@return a non-zero error code if	*/	OSStatus psSetupStreamInfoData(StreamInfoData *comm, PSStream *psStream, Collection hints);			/**		Given a StreamInfoData structure, returns true if the StreamInfoData 		indicates that it can send 8 bit characters	and false otherwise. 			Sending 8 bit characters means that characters with the high bit set in the byte		can be sent over the comm channel. This call says nothing about the low 32 control characters.				@param	comm	the #StreamInfoData# structure defining the current stream.				@return a #Boolean# that indicates whether #comm# can pass the low 32 control characters.	*/	Boolean psCanStreamDo8Bit(StreamInfoData comm);			/**		Configures a #StreamInfoData# structure so that it can pass 8 bit characters		if the doEightBit #Boolean# is true. If doEightBit is false, this call configures		the #StreamInfoData# structure so that it can not pass eight bit characters.								Passing 8 bit characters means that characters with the high bit set can be sent over		the communications channel. This call does not say anything about the low 32 control characters.				Note that making this call does not change the ability of any underlying communications channel to		transmit 8 bit data but only signals to output routines which use a #StreamInfoData structure#		that they can format their output using the high bit of each byte.				@param	comm	the #StreamInfoData# structure defining the current stream.				@param 	doEightBit	a #Boolean# that indicates whether #comm# can pass 8 bit characters.							If #doEightBit# is true, #comm# can pass 8 bit characters; if							#doEightBit# is false, #comm# can not can pass 8 bit characters					@return a non-zero code if the stream can not be configured.	*/	OSStatus psSetStream8Bit(StreamInfoData comm, Boolean doEightBit);			/**		Given a #StreamInfoData structure#, returns true if #comm# says it can pass the 		low 32 control characters and false if it can not.				@param	comm	the #StreamInfoData# structure defining the current stream.				@return a #Boolean# that indicates whether #comm# can pass the low 32 control characters.	*/	Boolean psCanStreamDoTransparent(StreamInfoData comm);		/**		Given a #StreamInfoData# structure, configures #comm# to say that it can pass the low 32 control		characters if the #doTransparent# Boolean is true. If #doTransparent# is false, configures the		#StreamInfoData# structure to say that it can not pass the low 32 control characters.			Note that making this call does not change the ability of any underlying communications channel to		transmit the low 32 control characters but only signals to output routines which use a StreamInfoData		structure that they can format their output using the low 32 control characters.				@param	comm	the #StreamInfoData# structure defining the current stream.				@param	doTransparent	a #Boolean# specifying whether the stream can pass the low 32 control								characters. If #doTransparent# is true, #comm# can pass low 32 control								characters; if #doTransparent# is false, #comm# can not pass low 32 control								characters.				@return a non-zero code if the stream can not be configured.	*/	OSStatus psSetStreamTransparent(StreamInfoData comm, Boolean doTransparent);			/**		Disposes of a #StreamInfoData structure# that was created and returned from		#psSetupStreamInfoData()#. Upon return of this routine, #*comm# is NULL.				@param	comm	the #StreamInfoData# structure to be disposed.				@return a non-zero code if #comm# can not be disposed. 	*/	OSStatus psDisposeStreamInfoData(StreamInfoData *comm);		/**		Returns the stream corresponding to #comm#.				@param	comm	the #StreamInfoData# structure containing the stream.				@return	a pointer to #PSStream# corresponding to #comm#.	*/	PSStream *psGetStreamFromStreamInfoData(StreamInfoData comm);			/**			psOutFormat is a simple printf like output mechanism. The supported formats are:		^b		pass in a long and either 'T' or 'F' is output.		^d		pass in a long and it is output in decimal format.		^f		pass in a 16.16 fixed number and it is output in decimal with up to 3 places past the decimal.		^F		pass in a 16.16 fixed number and it is output in decimal with up to 4 places past the decimal.		^H		pass in a long and the long div 2 is output with a possible .5		^s		pass in a pointer to a PString.		^S      same as ^s, but with control and extended ascii characters quoted. Typically used for DSC comments		^z      same as ^s, but specified with explicit length (call with string pointer and long length).		^Z      same as ^s, but generate (..) or <..> depending on which one takes the least space.			^i		pass in a short and it is output in decimal format.		^p		same as ^s, it outputs a Pascal String.		^h		takes a buffer pointer and a length byte. Outputs the bytes in hex.				This is a simple #printf()# like output mechanism.				@param	comm	a #StreamInfoData# structure defining the stream.				@param	format	reflects how the data is represented in the output.				@return	a non-zero code if the data could not be written.	*/	OSStatus psOutFormat(StreamInfoData comm, ConstStr255Param format, ...);						/**			Similar to #psOutFormat()# except that it takes a pointer to a #SubsectionStr#		structure rather than a format string. The #SubsectionStr# structure provides both		a format string and a PSSubsection value that will be passed to the stream's output		routine to identify the type of PostScript that is begin written. 			This flavor of this function writes a NULL #info# pointer in the		stream's #PSPosition# structure that is passed to the write routine.				@param	comm	a #StreamInfoData# structure defining the stream.				@param	format	a pointer to a #SubsectionStr# which reflects how the data is represented						in the output.								@return	a	non-zero code if the data could not be written.	*/	OSStatus psOutFormatPosition(StreamInfoData comm, const SubsectionStr *format, ...);		/**			Similar to #psOutFormatPosition()# except the #info# value passed to		this routine is written into the #comm#'s PSPosition structure that is passed to the write		routine.			The #info# pointer provides additional information to the PostScript positional information		provided by #format#. See the documentation on #PSSectionInfo.h# for more details.				@param	comm	a #StreamInfoData# structure defining the stream to which #info# is written.				@param	format	a pointer to a #SubsectionStr# which reflects how the data is represented						in the output.				@param	info	a pointer to the data to be written.						@return	a	non-zero code if the data could not be written.	*/	OSStatus psOutFormatPositionInfo(StreamInfoData comm, const SubsectionStr *format, void *info, ...);			/**			psOutBinaryBlock writes #nBytes# from #block# out. If #comm# indicates that it supports 8 bit		data then this routine emits binary data; otherwise it emits hex data.				@param	comm	a #StreamInfoData# structure defining the stream to which #nBytes# is written.				@param	block	the data to be written.				@param	nBytes	a long specifying the number of bytes of #block# to write.				@param	lineLength	a pointer to a #short# representing the desired length of the line.				@return	a	non-zero code if the data could not be written.	*/	OSStatus psOutBinaryBlock(StreamInfoData comm, void *block, long nBytes, short *lineLength);				/**			Writes the #nBytes# from #block# using the hex encoding technique, regardless of		the channel characteristics.				@param	comm	a #StreamInfoData# structure defining the stream to which #nBytes# is written.				@param	block	the data to be written.				@param	nBytes	a long specifying the number of bytes of #block# to write.				@param	lineLength	a pointer to a #short# representing the desired length of the line.				@return	a	non-zero code if the data could not be written.	*/	OSStatus psOutHexBlock(StreamInfoData comm, Byte *block, long nBytes, short *lineLength);				/**			Writes #nBytes# of data from #block# to 'comm without any additional processing.			@param	comm	a #StreamInfoData# structure defining the stream to which #nBytes# is written.				@param	block	the data to be written.				@param	nBytes	a long specifying the number of bytes of #block# to write.				@return	a	non-zero code if the data could not be written.	*/	OSStatus psOutBlock(StreamInfoData comm, const void *block, long nBytes);		/** 		Writes the byte #c# to #comm# 				@param	comm	a #StreamInfoData# structure defining the stream to which #c# is written.				@param	c		a #Byte# to be written to #comm#				@return a non-zero code if	*/	OSStatus psOutChar(StreamInfoData comm, Byte c);		/**			Writes the resource specified by #type# and #id# from the open resource file 'fRef'		to the stream defined by #comm#.						@param	comm	a #StreamInfoData# structure defining the stream to which the resource is written.				@param	fRef	a #short# representing the open resource file					@param	type	an #OSType# specifying the kind of resource.				@param	id	a long specifying the resource number of #type#.				@return a non-zero code if the resource could not be written.	*/	OSStatus psOutRes(StreamInfoData comm, short fRef, OSType type, long id);								/**		Writes the string #str# assuming that it is in a PostScript string.		This function performs the quoting necessary for the channel and does linebreaks		if necessary.				@param	comm	a #StreamInfoData# structure defining the stream to which #str# is written.				@param	str a pointer to a #Byte# which represents the data to write.				@param	length a long representing the amount of data from #str# to write.				@param	quoted	a #Boolean# indicating whether quoting is used. If #quoted# is true,						quoting is used; if #quoted# is false, quoting is not used.				@param	lineLength	a pointer to a #short# representing the desired length of the line.				@return	a non-zero code if #str# can ot be written.	*/	OSStatus psOutString(StreamInfoData comm, Byte *str, long length, Boolean quoted, short *lineLength);	/* BH012 */ 		/**		Obtains a hint handle from #hints# and writes it into the output		stream.  The desired collection item is specified by #theTag# and #theTagID#.				If the caller specifies #ignoreCollectionNotFoundErr# as true, if the hint is not		found in the collection, no error is returned by this routine; otherwise this routine		returns an error if the hint is not found.			@param comm	a #StreamInfoData# to which #hints# is written.				@param hints	a #Collection# from which to retrieve #theTag# and #theTagID#.				@param theTag	a #short# specifying the tag of the desired collection.				@param theTagID a #short# specifying the ID of #theTag#.				@param ignoreCollectionNotFoundErr	a #Boolean# indicating whether the #collectionItemNotFoundErr#											error is returned.				@return a non-zero code if #ignoreCollectionNotFoundErr# is true and the error is				#collectionItemNotFoundErr# or if the error is other than #collectionItemNotFoundErr#. 	*/	OSStatus psOutBlockHintHandle(StreamInfoData comm, Collection hints, CollectionTag theTag, 										short theTagID, Boolean ignoreCollectionNotFoundErr);			/**				Reads up to #*nBytes# of data into the buffer passed in as #block#. The number of bytes		actually read is returned as #*nBytes#.				Note that this routine does not check whether the stream represented by #comm# actually has a		read procedure; it is up to the caller to check prior to calling #psInBlock()#.					@param	comm	a #StreamInfoData# structure representing the stream.				@param block	the buffer that into which the data is read. 				@param	nBytes	a #long# reresenting the number of bytes actually read.				@return a non-zero code if the data can not be read into the buffer.	*/	OSStatus psInBlock(StreamInfoData comm, void *block, long *nBytes);						/**			Writes a pstring to comm.				@param	comm	a #StreamInfoData# structure which represents the stream.				@param	pstr	a #ConstStr255Param# representing the data to write to #comm#.				@return	a non-zero code if #pstr# can not written to #comm#.	*/	OSStatus psOutPStr(StreamInfoData comm, ConstStr255Param pstr);						/**			Sets the PSSection field of the stream represented by 'comm' to 'psSection'.				@param	comm	a #StreamInfoData# structure which represents the stream.				@param	psSection	a #PSSection# structure. The #PSSection# field of #comm#							is set to the information contained here.				@return	a non-zero code if #psSection# can not written to #comm#.	*/	void psSetFormatSection(StreamInfoData comm, PSSection psSection);					/**			Gets the #PSSection# field of the stream represented by #comm#.				@param comm	a #StreamInfoData# structure which represents the stream.				@return	a non-zero code if the #PSSection# field can not be found.			*/	PSSection psGetFormatSection(StreamInfoData comm);								/**				Sets up and opens up a #*streamP# corresponding to the output device represented by #papaH#.		The stream represented by #*streamP# is filled in accordingly.				The caller supplies a #hints# collection which may contain hints to the streams code		as to how to configure the #*streamP#.				#*statusP# points to a #StatusProcs# structure that specifies the status output routine		callbacks the caller wishes to have called by the streams code. The data in the #StatusProcs#		structure is copied by #psOpenPSOutputStream()# into the stream so that this data does not have		to be allocated for the duration of the #*streamP#'s usage.					@param hints	a #Collection# containing hints about how to configure #*streamP#.				@param 	streamP	a pointer to a #PSStream# structure representing the stream to open and set up.				@param 	statusP a pointer to a #StatusProcs# structure that specifies the status output routine						callbacks.				@param papaHandle	the #PAPA# for that selected printer. 				@return	a non-zero code if the stream can not be opened or set up.	*/	OSStatus psOpenPSOutputStream(Collection hints, PSStream *streamP, StatusProcs *statusP, Handle papaH);		/**			Closes and releases any memory used by #*streamP#.			@param stream	a pointer to a #PSStream# structure representing the stream to close.				@return	a non-zero code if the stream can not be closed.	*/	OSStatus psClosePSOutputStream(PSStream *stream);			/**			Sets up #*streamP# so that calling the input routine reads the file represented by #*specP#.		Calling the write routine on #*streamP# generates calls to #clientProc# with the #refcon# passed in.				@param FSSpec	a pointer to a #FSSpec# structure representing the stream to open. 				@param streamP	a pointer to a #PSStream# structure representing the stream to set up.				@param refcon	 client-supplied data to be used by #clientProc#				@param clientProc	client-supplied proc				@return a non-zero code if there was an error while opening the stream.	*/	OSStatus psOpenFileInputStream(const FSSpec *specP, PSStream *streamP, void *refcon, clientDataProc clientProc);		/**			Closes and releases any memory used by a #*stream#.				@param stream a pointer to a #PSStream# structure representing the stream to close.  				@return a non-zero code if there was an error while closing the stream.	*/	OSStatus psCloseFileInputStream(PSStream *stream);					/*	psOutBlockPositionInfo writes 'nBytes' of data from 'block' unprocessed to the stream 'comm. 			Writes 'nBytes' of data from 'block' unprocessed to the stream 'comm.				The data is marked with the PSSubsection specified by 'subsection' together with the tagging information 		provided by 'info'.				Available in PrintingLib 8.7 and later only.			*/	OSStatus psOutBlockPositionInfo(StreamInfoData comm, PSSubsection subsection, void *info, 											const void *block, long nBytes);	#if PRAGMA_STRUCT_ALIGN	#pragma options align=reset#elif PRAGMA_STRUCT_PACKPUSH	#pragma pack(pop)#elif PRAGMA_STRUCT_PACK	#pragma pack()#endif#ifdef PRAGMA_IMPORT_OFF#pragma import off#elif PRAGMA_IMPORT#pragma import reset#endif#ifdef __cplusplus}#endif#endif	/* __PSSTREAMS__	*/