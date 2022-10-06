#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>

class conf{

    public:
        conf(std::string path_to_conf)
        {
            conf_path = path_to_conf;
            openConf();
        }

        void insert(std::string setting, std::string value)
        {
            setNewline();
            conf_file << setting << '=' << value;
        }
        void insert(std::string setting, char& value)
        {
            setNewline();
            conf_file << setting << '=' << value;
        }
        void insert(std::string setting, int value)
        {
            setNewline();
            conf_file << setting << '=' << value;
        }
        void insert(std::string setting, double value)
        {
            setNewline();
            conf_file << setting << '=' << value;
        }

        void updateSetting(std::string setting_old, std::string setting_new)
        {
            update(setting_old, setting_new, 1);
        }

        void updateValue(std::string setting, std::string value)
        {
            update(setting, value);
        }
        void updateValue(std::string setting, int value)
        {
            update(setting, std::to_string(value));
        }
        void deleteSetting(std::string setting)
        {
            update(setting, "", 3);
        }

        std::string getLine(long long pointer_pos, char delimiter = '\n')
        {
            std::string returnLine;
            long long size = 0;

            // get length of file
            conf_file.seekg(0, std::ios::end);
            size_t len = conf_file.tellg();

            conf_file.seekp(pointer_pos);
            while (conf_file.get() != delimiter){}
            size = (long long) conf_file.tellp() - pointer_pos;
            conf_file.seekp(pointer_pos);
            char line[size];
            conf_file.get(line, size);
            for (size_t i = 0; i < size; i++)
                returnLine += line[i];
            getLine_pos = (long long) conf_file.tellp() + 1;
            if (getLine_pos >= len)
                getLine_pos = -1;

            return returnLine;
        }

        std::string getSettingLine(std::string setting) // return string containing setting
        {
            std::string line;
            getLine_pos = 0;

            while (getLine_pos != -1)
            {
                line = getLine(getLine_pos);
                if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                {
                    return line;
                }
            }
            return "";
        }

        std::string getValue(std::string setting)
        {
            std::string line = getSettingLine(setting);
            std::string value = line.substr(line.find('=') + 1, line.length() - line.find('=') -2);
            return value;
        }

        std::string getLineValue(std::string line)
        {
            std::string value = line.substr(line.find('=') + 1, line.length() - line.find('=') -2);
            return value;
        }

        void closeConf()
        {
            conf_file.close();
        }

    private:
        std::string conf_path;
        std::fstream conf_file;
        long long getLine_pos = 0;

        void openConf()
        {
            conf_file.open(conf_path.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
            if (!conf_file.is_open())
                std::cout << "Could not create / open conf file: " + conf_path << std::endl;
        }

        void setNewline()
        {
            conf_file.seekg(0, conf_file.end);
            conf_file.unget();
            char lastChar = conf_file.get();
            if (lastChar != '\n')
                conf_file.put('\n');
        }

        void update(std::string setting, std::string value, int opper = 0) // opper == 0 updateval; opper == 1 updateSet; opper == ? deleteSet 
        {
            closeConf();

            std::string line;
            std::string confTemp_path = "./." + conf_path.substr(conf_path.rfind('/') +1, conf_path.length() - conf_path.rfind('/') - 1);
            std::ifstream mainConf(conf_path.c_str());
            std::ofstream confCopy(confTemp_path.c_str());
            if (mainConf && confCopy)
            {
                std::cout << "Ready to copy" << std::endl;
                while (getline(mainConf, line))
                {
                    if (line.find(setting.c_str(), 0, line.find('=')) != std::string::npos)
                    {
                        if (opper == 0)
                        {
                            std::cout << "setVal: " << setting << '=' << value << '\n';
                            confCopy << setting << '=' << value << '\n';
                        }
                        else if (opper == 1)
                        {
                            std::cout << "setSet: " << value << '=' << getLineValue(line) << '\n';
                            confCopy << value << '=' << getLineValue(line) << '\n';
                        }
                        else
                        {
                            std::cout << "delSet: " << setting << '=' << value << '\n';
                        }
                    }
                    else
                    {
                        std::cout << "stdCpy: " << line << '\n';
                        confCopy << line << '\n';
                    }
                }
                std::cout << "Copied!" << std::endl;
                
            }else{
                std::cout << "Cannot read file" << std::endl;
            }
            mainConf.close();
            confCopy.close();
            remove(conf_path.c_str());
            rename(confTemp_path.c_str(), conf_path.c_str());

            openConf();
        }
};

int main(int argc, char const *argv[])
{
    conf conf("./main.conf");

    std::cout << conf.getValue("url") << std::endl;

    std::string setting_base = "default";
    for (int i = 0; i < 15; i++)
    {
        std::string setting = setting_base + std::to_string(i);
        conf.insert(setting, i);
    }
    conf.updateValue("default8", "5002");
    conf.updateSetting("default10", "setting1");
    conf.updateValue("setting1", "1");

    conf.closeConf();

    return 0;
}
