NAME=$(echo "$1" | cut -d '.' -f 1)
size=${#NAME} 
header="=="
for i in $(seq 1 $size); do header="${header}="; done

echo "==================$header======================================"
echo "======================= EXECUTING $NAME ======================="
echo "==================$header======================================"
echo
gcc -o ./.bin/$NAME $1
./.bin/$NAME
rm .bin/$NAME
echo
echo