/**	@name  PSLogFolder.h*/	/**		@name Introduction		This file contains prototypes for routines useful for creating files in the Printing Logs Folder.	*//*	File:		PSLogFolder.h	Contains:	This file contains prototypes for routines useful for creating files in the Printing Logs Folder.  	Version:	Technology:	PrintingLib 8.7 				Release:	1.0 	Copyright:	� 1999 by Apple Computer Inc. All Rights Reserved. 	Bugs?:		For bug reports, consult the following page on 				the World Wide Web:  					http://developer.apple.com/bugreporter/*/#ifndef __PSLOGFOLDER__#define __PSLOGFOLDER__#ifndef __MACTYPES__#include <MacTypes.h>#endif#ifndef __FILES__#include <Files.h>					#endif#ifndef __COLLECTIONS__#include <Collections.h>			#endif#if PRAGMA_ONCE#pragma once#endif#ifdef __cplusplusextern "C" {#endif#if PRAGMA_IMPORT#pragma import on#endif#if PRAGMA_STRUCT_ALIGN	#pragma options align=mac68k#elif PRAGMA_STRUCT_PACKPUSH	#pragma pack(push, 2)#elif PRAGMA_STRUCT_PACK	#pragma pack(2)#endif/*** Defines ***//***************//*** Prototypes ***//******************/OSStatus psMakeLogFileSpec(Collection hints, FSSpec *fsSpecP, Str15 suffix);					/*	DMG600	psMakeLogFileSpec fills in fsSpecP. It uses the hints collection to obtain the proper folder for	the log file (resolving aliases as necessary) and the root name of the job. It appends the suffix	to the root name. The final fsSpec is ready for numberedFileName, should that be appropriate.*/OSStatus psMakeNumberedFilename(FSSpec *fileP, Boolean *updatedP, Boolean tryDelete);			/*	Given the volume, directory ID, and base filename in	the filespec 'file', add a number to the base filename	in order to name a unique file. If for instance the	name in 'file' is file.ps then this function will	try to make a name like file.1.ps. If file.1.ps exists	the we make file.2.ps and so on. On return if this	function made a unique name it returns noErr and 'file->name'	has been changed to the unique filename. If we couldn't	make a unique name then we return an error code:	errCouldNotMakeNumberedFilename.	if updatedP is non-NULL then the boolean value it points to will be updated to reflect	whether psMakeNumberedFilename actually updated the filename in the FSSpec pointed to	by fileP.		If the boolean tryDelete is true, then psMakeNumberedFilename will delete an existing	file (if it can) rather than make a unique new name.*/#if PRAGMA_STRUCT_ALIGN	#pragma options align=reset#elif PRAGMA_STRUCT_PACKPUSH	#pragma pack(pop)#elif PRAGMA_STRUCT_PACK	#pragma pack()#endif#ifdef PRAGMA_IMPORT_OFF#pragma import off#elif PRAGMA_IMPORT#pragma import reset#endif#ifdef __cplusplus}#endif#endif		