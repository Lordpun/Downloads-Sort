# Downloads Sort
This is a small script to automatically move and sort files you download  

## Installing
### Precompiled builds
Simply download the latest version under the releases tab for your OS  
**Note**: I've noticed that the precompiled versions (At least the Linux version) don't work, so compiling from source is the only option

### From Source

#### Dependencies
* C++ (Minimum version: 17)
* Cmake (Minimum version: 3.14)

#### Compiling
Run :  
`git clone https://Lordpun/Downloads-Sort`  
`cd Downloads-Sort`  
`./run.sh`  
  
The executable should be at `./build/Downloads-Sort`  

## Using
### Generating the config
Run the executable  
It should automatically generate a config file  
  
The config file is found at:  
**Windows**: `C:\Users\user\AppData\Roaming\Downloads-Sort\config.toml`  
**Linux**: `/home/user/.config/Downloads-Sort/config.toml`  
**MacOS**: `/home/user/Library/Application Support/Downloads-Sort/config.toml`  
If your config folder couldn't be detected, it will generate a folder called `Downloads-Sort-Config/config.toml`  

### Config format

The format is:  
```
downloads-path = "path/to/downloads"

[[sort-paths]]
extensions = []
sort-path = "path/to/sort"
```

There are some extensions automatically generated, but there's no sort and downloads path  
For each group of extensions, simply make a new [[sort-paths]] group  

### Running
Simply run the executable and it will run in the background  
You can verify it's running by either checking with something like Task Manager or add something to your downloads folder and see if it moves  
  
It will wait for a file to be added to your downloads and then move it if the file's extension is listed in the config
