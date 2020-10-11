#######################################_
Proj  = Rubik
Debug = -g
Flags = ${Debug} -Wall -std=c++17
Src   = ${Proj}.cpp
Obj   = ${Proj}.o
#######################################_
${Proj}: ${Obj}
	g++ ${Flags} -o $@ $^
#######################################_
${Obj}: ${Src}
	g++ ${Flags} -c $<
#######################################_
clean:
	${RM} -v ${Proj} ${Obj}
#######################################_
# > use wilcard to get Obj from Src
