find $(awk -F ":" '$1 == s62445 {print $6}' /etc/passwd) -type f -printf "%T@t %n %i %p\n"|awk -F " " '$2>1 {print $0}'|sort -n|tail -n 1|cut -d " " -f3
