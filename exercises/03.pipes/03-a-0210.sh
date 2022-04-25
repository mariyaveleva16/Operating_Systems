cut -d ":" -f1,5 /etc/passwd
awk -F ":" '{print $1" "$5}' /etc/passwd
