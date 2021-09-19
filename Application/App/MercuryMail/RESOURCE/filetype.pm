;
;  Pegasus Mail System,
;  Copyright (c) 1990-97, David Harris, All Rights Reserved.
;
;  File Typing Rules
;
;  This file is used by Pegasus Mail to determine the "attachment type"
;  information for files automatically. It consists of rules that can
;  test a file's extension and any byte or strings in the first 512
;  bytes of the file. Each line contains the complete set of rules for
;  a single type of file, in the following format:
;
;     <file type>,<match type>,<operation>[,<operation>...]
;
;     "file type" is the WinPMail "attachment type" string that
;         should be used if a file matches this rule.
;
;     "match type" is one of the following values:
;         0 : Match is good if any operation succeeds
;         1 : Match is only good if all operations succeed
;
;     "operation" is one or more groups of three parameters in
;     the following format:
;         <opcode>,<offset>,<string>
;             "opcode" is one of the following characters:
;                 X : match the file's extension
;                 B : match the single byte contained in "string"
;                     at offset "offset" in the file
;                 S : match the string contained in "string" starting
;                     at offset "offset" in the file
;                 R : match the string contained in "string" anywhere
;                     in the first 512 bytes of the file
;             "offset" is the offset to start matching in the file. When
;                 "operation" is either X or R, it should be set to 0
;             "string" is the string or byte to match. It can be ASCII
;                 characters, or escapes in the form "\xxx", where "xxx"
;                 is exactly three decimal characters.
;
;   Examples:
;      MS-Word,0,X,0,.DOC
;         - Returns "MS-Word" if the file's extension is ".DOC".
;
;      PGP-Public-Key,0,R,0,BEGIN PGP PUBLIC
;         - Returns "PGP-Public-Key" if the string "BEGIN PGP PUBLIC"
;           appears anywhere in the first 512 bytes of the file.
;
;     PCEXE,1,X,0,.EXE,S,0,MZ
;         - Returns "PCEXE" if the file's extension is ".EXE"
;           AND the first two characters in the file are "MZ".
;
;      ZIP-Archive,0,X,0,.ZIP,S,0,PK\003
;         - Returns "ZIP-Archive" if the file's extension is ".ZIP"
;           OR the first three characters are "PK" and an ASCII 3.
;
;  The matching process ends on the first viable match. Because of this,
;  if you have both a specific set of rules and a general set of rules
;  for any single file type, you should always place the general rules
;  after the specific rules in the file to allow more reliable matching.
;
;  The parser for this file is inflexible - you must get the format
;  right. Note in particular that whitespace is not permitted, or if it
;  is present, it is assumed to be significant. The only valid delimiter
;  in this file is a comma; the only way you can match a comma in a
;  string is by using the escape "\044".
;
;  Blank lines and lines in this file starting with ';' or '#' are
;  regarded as comments and are ignored.
;

MS-Word,1,S,0,\219\165\045
PCEXE,1,X,0,.EXE,S,0,MZ
PCEXE,1,X,0,.DLL,S,0,MZ
ZIP-archive,0,X,0,.ZIP,S,0,PK\003
MS-Richtext,0,X,0,.RTF,S,0,{\092rtf
Program-source,0,X,0,.C,X,0,.H,X,0,.PAS,X,0,.RC,X,0,.CPP,X,0,.BAS,X,0,.ASM
GIF-image,0,X,0,.GIF,S,0,GIF
JPEG-image,0,X,0,.JPG,S,6,JFIF
BMP-image,0,X,0,.BMP,X,0,.DIB,S,0,BM
WAV-sound-file,1,S,0,RIFF,S,8,WAVE
WAV-sound-file,0,X,0,.WAV
WordPerfect,0,S,1,WPC
Excel-sheet,0,X,0,.XLS
Excel-chart,0,X,0,.XLC
MS-Access,0,X,0,.MDB
AVI-Movie,1,S,0,RIFF,S,8,AVI
AVI-Movie,0,X,0,.AVI
Windows-help,1,X,0,.HLP,S,0,?_\003
HTML-text,0,X,0,.HTM
HTML-text,1,S,0,<HTML>
PGP-Public-Key,0,R,0,BEGIN PGP PUBLIC
PGP-encrypted,0,X,0,.PGP
Text,0,X,0,.TXT

