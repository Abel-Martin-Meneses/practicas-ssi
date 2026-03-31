# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++17 -Wall -O2

# Ejecutable
TARGET = cifrado_vigenere

# Directorio de objetos
OBJDIR = obj

# Fuentes y objetos
SOURCES = $(wildcard *.cc)
OBJECTS = $(patsubst %.cc,$(OBJDIR)/%.o,$(SOURCES))

# Regla por defecto
all: $(TARGET)

# Enlazar objetos para crear el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar cada .cc en obj/
$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorio obj si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpiar
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean