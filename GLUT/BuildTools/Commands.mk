#=============================================================================#
ifeq ($(OS),Windows_NT)
#=============================================================================#
# Redirects stdout and stderr to the null device and resets the errorlevel to 0.
ignore-err = > NUL 2>&1 & verify > NUL

# Set the shell to the native Windows shell.
SHELL = cmd.exe

# Set the binary file extension.
BINARY = .exe

# Change directory
# $(1) - target directory.
CHDIR = cd /D $(1)

# Create a directory and needed parent directories.
# $(1) - the directory to create.
MKDIR = mkdir $(subst /,\,$(1)) $(ignore-err)

# Recursively remove a directory.
# $(1) - the directory to remove.
RMDIR = rd /s /q $(subst /,\,$(1)) $(ignore-err)

# Remove a file.
# $(1) - the file to delete.
RM = del /q  $(subst /,\,$(1)) $(ignore-err)

# Copy a file.
# $(1) - the source file.
# $(2) - the target file.
CP = copy  /y $(subst /,\,$(1))  $(subst /,\,$(2)) > NUL

# Rename a file.
# $(1) - original file name.
# $(2) - new file name.
RENAME = move $(subst /,\,$(1)) $(subst /,\,$(2)) $(ignore-err)

# The character used to seperate commands.
SEP = &

# The character used to seperate paths.
PATH_SEP =;

# Copy a directory
# &(1) - Source directory
# &(2) - Destination directory
CPDIR = xcopy $(subst /,\,$(1)) $(subst /,\,$(2)) /q /e /h /s /y $(ignore-err)

# Copy a directory contents
# &(1) - Source directory
# &(2) - Destination directory
CPDIRC = xcopy $(subst /,\,$(1)) $(subst /,\,$(2)) /q /e /h /s /y $(ignore-err)

#=============================================================================#
else
#=============================================================================#
# Set the number of computing cores.
NUMBER_OF_PROCESSORS = $(shell grep -c ^processor /proc/cpuinfo)

# Change directory
# $(1) - target directory.
CHDIR = cd $(1)

# Create a directory and needed parent directories.
# $(1) - the directory to create.
MKDIR = mkdir -p $(1)

# Recursively remove a directory.
# $(1) - the directory to remove.
RMDIR = rm -r -f $(1)

# Remove a file.
# $(1) - the file to delete.
RM = rm -f $(1)

# Copy a file.
# $(1) - the source file.
# $(2) - the target file.
CP = cp $(1) $(2)

# Rename a file.
# $(1) - original file name.
# $(2) - new file name.
RENAME = mv $(1) $(2)

# The character used to seperate commands.
SEP = ;

# The character used to seperate paths.
PATH_SEP =:

# Copy a director
# &(1) - Source directory
# &(2) - Destination directory
CPDIR = cp -r $(1) $(2)/

# Copy a directory contents
# &(1) - Source directory
# &(2) - Destination directory
CPDIRC = cp -rf $(1)/* $(2)/

#=============================================================================#
endif
#=============================================================================#