CXX      := g++
CXXFLAGS := -pipe -std=c++14 -O2 -Wall -Wextra -pedantic

TARGET := test
SRCS   := test.cpp
OBJS   := $(SRCS:.cpp=.o)

TESTDIR   := tests
MANIFEST  := $(TESTDIR)/tests.txt

# -------------------------
# Default
# -------------------------
all: build

# -------------------------
# Build
# -------------------------
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# -------------------------
# Generate test manifest
# -------------------------
$(MANIFEST):
	@echo "Generating test manifest..."
	@ls $(TESTDIR) | grep -v '\.a$$' > $(MANIFEST)

manifest: $(MANIFEST)

# -------------------------
# Run all tests
# -------------------------
test: build manifest
	./$(TARGET) --test

# -------------------------
# Run a single test
# Usage: make test-one NAME=test1
# -------------------------
test-one: build
	@if [ -z "$(NAME)" ]; then \
		echo "Usage: make test-one NAME=<testname>"; \
		exit 1; \
	fi
	@echo "$(NAME)" > $(MANIFEST)
	./$(TARGET) --test

# -------------------------
# Cleanup
# -------------------------
clean:
	rm -f $(OBJS) $(TARGET) $(MANIFEST)

.PHONY: all build test test-one clean manifest
