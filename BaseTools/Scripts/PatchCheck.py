import email.header

                not lines[i].startswith('git-svn-id:') and
                not lines[i].startswith('Reviewed-by') and
                not lines[i].startswith('Acked-by:') and
                not lines[i].startswith('Tested-by:') and
                not lines[i].startswith('Reported-by:') and
                not lines[i].startswith('Suggested-by:') and
                not lines[i].startswith('Signed-off-by:') and
                not lines[i].startswith('Cc:')):
                if self.filename == '.gitmodules' or \
                   self.filename == 'BaseTools/Conf/diff.order':
                    # .gitmodules and diff orderfiles are used internally by git
                    # use tabs and LF line endings.  Do not enforce no tabs and
                    # do not enforce CR/LF line endings.
        if self.force_crlf and eol != '\r\n' and (line.find('Subproject commit') == -1):