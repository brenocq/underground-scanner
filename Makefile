CC = g++
INCLUDE = -I. -I./extern/ 
LIBS = -lglfw -lGL -lX11 -lXrandr -lXi -ldl 
FLAGS = -g
# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

OBJ = obj/

FILES_SRC = main maze
FILES_SRC_GFX = graphics shader camera userInterface
FILES_EXT_IMGUI = imgui imgui_demo imgui_draw imgui_widgets imgui_tables imgui_impl_glfw imgui_impl_opengl3
FILES_EXT_GLAD = glad

SOURCES = $(patsubst %, %.cpp, ${FILES_SRC})
SOURCES += $(patsubst %, graphics/%.cpp, ${FILES_SRC_GFX})
SOURCES += $(patsubst %, extern/imgui/%.cpp, ${FILES_EXT_IMGUI})
SOURCES += $(patsubst %, extern/glad/%.c, ${FILES_EXT_GLAD})

OBJECTS = $(patsubst %, ${OBJ}%.o, ${FILES_SRC})
OBJECTS += $(patsubst %, ${OBJ}%.o, ${FILES_SRC_GFX})
OBJECTS += $(patsubst %, ${OBJ}%.o, ${FILES_EXT_IMGUI})
OBJECTS += $(patsubst %, ${OBJ}%.o, ${FILES_EXT_GLAD})

${OBJ}%.o: %.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c ${INCLUDE} ${LIBS} ${FLAGS} $< -o $@

${OBJ}%.o: graphics/%.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c ${INCLUDE} ${LIBS} ${FLAGS} $< -o $@

${OBJ}%.o: extern/imgui/%.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c ${INCLUDE} ${LIBS} ${FLAGS} $< -o $@

${OBJ}%.o: extern/glad/%.c
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c ${INCLUDE} ${LIBS} ${FLAGS} $< -o $@

all: ${OBJECTS}
	@/bin/echo -e "${GREEN}${BOLD}----- Generating executable -----${NC}"
	${CC} ${OBJECTS} ${INCLUDE} ${LIBS} ${FLAGS} -o maze

clean:
	@/bin/echo -e "${GREEN}${BOLD}----- Cleaning project -----${NC}"
	rm -rf ${OBJ}*.o
	rm -rf maze

run: all
	@/bin/echo -e "${GREEN}${BOLD}----- Running maze -----${NC}"
	./maze
