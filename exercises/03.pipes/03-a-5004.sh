grep "$(cut -d ":" -f5|cut -d "," -f1|grep " "|awk -F " " '{l=length($2); if(l<=7) {print $1" "$2}}')" /etc/passwd
