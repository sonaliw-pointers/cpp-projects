
# console application name
LINK_TARGET = assignmentP2

# supporting classes 
OBJS =  \
 Node.o \
 NodePriorityQ.o \
 Tour.o \
 InputFileDecoder.o \
 OutputPrinter.o \
 assignmentP2.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)


# All Rule
all					: 	$(LINK_TARGET)


# Link Rule
# $@ expands to the rule's target, in this case "assignmentP2".
# $^ expands to the rule's dependencies, in this case the six files
# assignmentP2.o, OutputPrinter.o, InputFileDecoder.o, Tour.o, NodePriorityQ.o and Node.o
$(LINK_TARGET) 		: 		$(OBJS)
					g++ -g -o $@ $^ -std=c++11

# Compilation only Rule				
# Pattern rule to create a file with a .o suffix, given a file with a .cpp suffix.
# $@ for the pattern-matched target
# $< for the pattern-matched dependency			
%.o					:		%.cpp
					g++ -g -o $@ -c $< -std=c++11


# Dependency rules
assignmentP2.o 		: 		OutputPrinter.h InputFileDecoder.h Tour.h stdafx.h
OutputPrinter.o 	: 		OutputPrinter.h Tour.h stdafx.h
InputFileDecoder.o 	: 		InputFileDecoder.h Tour.h stdafx.h
Tour.o 				: 		Tour.h NodePriorityQ.h Node.h stdafx.h
NodePriorityQ.o 	: 		NodePriorityQ.h  Node.h  stdafx.h 
Node.o 				: 		Node.h stdafx.h 
stdafx.o 			: 		stdafx.h 

# Clean rule
clean				:
				rm -f $(REBUILDABLES)
				
