awk 'END{print NR}' emp.data
awk 'FNR == 3 {print}' emp.data
awk '{print $(NF)}' emp.data
awk 'END{print $(NF)}' emp.data
