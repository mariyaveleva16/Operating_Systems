grep $(whoami) /etc/passwd
grep $(whoami) -B 2 /etc/passwd
grep $(whoami) -B 2 -A 3 /etc/passwd
grep $(whoami) -B 2 /etc/passwd|head -n 1
