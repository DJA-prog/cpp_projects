vector<string> getlines(string file_path, string containing)
{
    fstream index_file;
    string file_content_line;
    vector<string>  images_list;
    index_file.open(file_path, ios::in);
    if (index_file.is_open()){ 
      	while(getline(index_file, file_content_line)){
              if (file_content_line.find(containing) != string::npos)
              {
                images_list.push_back(file_content_line);
              }
      	}
      	index_file.close(); //close the file object.
   	}else{
   		cout << "could not open " << file_path << endl;
   	}
    return images_list;
}