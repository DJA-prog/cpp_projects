# conf.cpp

includes used:
    #include <iostream>
    #include <stdio.h>
    #include <cstring>
    #include <fstream>

## class conf

## constructor
*  conf(std::string path_to_conf)

## public functions
*  conf(std::string path_to_conf)
    open new config file

*  void insert(std::string setting, std::string value)  // value types: std::string ; char& ; int ; double
    append setting to bottom of conf file

*  void updateSetting(std::string setting_old, std::string setting_new)
    update the setting name

*  void updateValue(std::string setting, std::string value) // value types: std::string ; int
    update the value of a setting

*  void deleteSetting(std::string setting)
    delete setting line

*  std::string getLine(long long pointer_pos, char delimiter = '\n')
    return string segment from pointer to before delimiter

*  std::string getSettingLine(std::string setting)
    return string of whole setting line

*  std::string getValue(std::string setting)
    return string of setting value

*  std::string getLineValue(std::string line)
    return string value from setting line

*  void closeConf()
    close config file

## private variables
*  std::string conf_path;
*  std::fstream conf_file;
*  long long getLine_pos = 0;

## private functions
*  void openConf()
    open confog file

*  void setNewline()
    append '\n' at the end of file as well as the pointer

*  void update(std::string setting, std::string value, int opper = 0)
    perform the opperatio of updating settings and deleting settings
    opper == 0 updateval; opper == 1 updateSet; opper == ? deleteSet
