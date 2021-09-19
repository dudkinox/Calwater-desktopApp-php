;
; Pegasus Mail MIME Mapping file.
; This file is used to add MIME content-type mappings into Pegasus Mail
;
; Each line in the file defines a bi-directional mapping between a MIME
; content type on the left and a Pegasus Mail attachment type on the
; right.
;
; When you add an attachment to a message, WinPMail will look through
; this file looking for an attachment type match; when it finds one, it
; will write the attachment using that MIME content type.
;
; When looking for viewers, Pegasus Mail performs the reverse of the
; same search, looking for a line containing a content type that matches
; the one used to send the file; if it finds one, it searches its list
; of attachment viewers for the attachment type defined on the same line.
;
; The format of this file is:
;
;       content_type = attachment_type
;

Text/HTML = HTML-text

