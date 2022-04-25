cut -d "/" -f2 /etc/passwd
awk -F "/" '{print $2}' /etc/passwd
