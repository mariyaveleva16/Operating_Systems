mkdir myetc
find /etc -perm /444 -type f -exec cp {} /home/students/s62445/myetc \;
