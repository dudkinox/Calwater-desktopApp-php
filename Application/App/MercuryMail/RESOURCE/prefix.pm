;
; PREFIX.PM - user-defined subject prefix "ignore" list
; Use this file to create your own list of strings that
; Pegasus Mail should ignore at the start of the subject
; line when sorting by thread or sorting by subject.
;
; This file can be placed either in the user's mailbox
; directory (in which case it will be private to that user),
; or in the same directory as WINPM-32.EXE, in which case it
; will be system-wide and used by anyone who runs that copy
; of the program.
;
; Each line in this file should be an absolutely literal
; string that Pegasus Mail should check for: spaces are
; significant, both leading and trailing. Any line starting
; with ';' or '#' is regarded as a comment and is ignored,
; as are blank lines.
;
; You can enter more complex expressions by making the first
; character on the line a tilde (~). Everything that follows
; the tilde is regarded as an extended Pegasus Mail v4.1
; regular expression, and it *must* contain the special
; sequence  /h  to show Pegasus Mail the point in the string
; where the prefix ends. As an example, consider this
; expression:
;
;      ~RE/w[[][0-9]+][ :]/h*
;
; This tells Pegasus Mail to look for any line starting with
; the letters "RE" followed by zero or more spaces, followed
; by a '[' character, followed by one or more digits, followed
; by a ']' character, followed by either a space or a colon.
; The  /h  indicates that this is where the prefix ends, while
; the '*' operator is used to match the remainder of the line.
;
; The items in this sample file are exactly the same as the
; default list built into Pegasus Mail itself (the list that
; it will use automatically if this file is not present). Note
; that Pegasus Mail will check for any combination that may be
; present of any item in this file - so, using this set of
; definitions, the subject lines "Re: (FWD) re FW: X" and
; "Re: X" will sort the same.

RE:
RE 
FWD:
(FWD)
FW:
~RE/w[[][0-9]+][ :]/h*
AW:
WG:

