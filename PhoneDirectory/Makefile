
# console application name
LINK_TARGET = pbirada1_phone_directory.out

# supporting classes 
OBJS =  \
 contactDetails.o\
 ContactDirectory.o \
 pbirada1_phone_directory.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)


# All Rule
all					: 	$(LINK_TARGET)



$(LINK_TARGET) 		: 		$(OBJS)
					g++ -g -o $@ $^ -std=c++11
	
%.o					:		%.cpp
					g++ -g -o $@ -c $< -std=c++11

# Clean rule
clean				:
				rm -f $(REBUILDABLES)
				
