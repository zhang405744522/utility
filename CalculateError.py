#!usr/bin/python
#coding:utf-8

import os
import re


def calculate_error(path, result_path_file):
    total_error = 0
    time_begin = 0
    result_index = 0
    error_dict = {}
    files = os.listdir(path)
    print files
    try:
        file_result = open(result_path_file, 'w')
        for file_handle in files:
            # print file
            error_counter = 0
            print path+file_handle
            if not os.path.isfile(path+file_handle):
                continue
            file_obj = open(path+file_handle)

            for line in file_obj:
                # print line
                match_object = re.search('Error', line)
                if match_object:
                    #print line
                    time_now = long(line[0:2]) * 60 * 60 + long(line[3:5]) * 60 + long(line[6:8])
                    '''if time_now - time_begin >= 3600:
                        time_begin = time_now
                        #file_result.write("index:")
                        #file_result.write(str(result_index))
                        file_result.write("\r\n")
                        result_index += 1
                        for k, v in error_dict.items():
                            file_result.write("key:")
                            file_result.write(k)
                            file_result.write(" value:")
                            file_result.write(str(v))
                            file_result.write("\r\n")
                            #print 'key:%s value:%d' % (k, v)
                        error_dict.clear()
                    '''
                    #try:
                    match_reg = re.search("(\[.+?\]).+?(\[.+?\]).*?(\[.+?\])", line)
                    if match_reg:
                        match_word = match_reg.group(3)
                        #print match_word
                        match_key = match_word[8:len(match_word)-1]
                        #print match_key
                        #if not cmp(match_key, 'error'):
                        #    print line
                        if match_key not in error_dict:
                            error_dict[match_key] = 1
                        else:
                            error_dict[match_key] += 1;
                        #print error_dict[match_key]
                    else:
                        print 'none match'
                    """
                    except:
                    #except Exception e:
                        print "re.search key error"
                        pass
                    """

                    error_counter += 1
            total_error += error_counter
            print 'FileName:%s,ErrorConter:%d' % (file_handle, error_counter)

            file_result.write("\r\n")
            file_result.write(file_handle)
            file_result.write("\r\n")
            for (k, v) in error_dict.items():
                print 'last key:%s value:%d' % (k, v)
                file_result.write("key:")
                file_result.write(k)
                file_result.write(" value:")
                file_result.write(str(v))
                file_result.write("\r\n")
    finally:
        file_obj.close()
        file_result.close()
        print 'TotalError:%d' % total_error

if __name__ == '__main__':
    print 'Begin'
    #calculate_error('/mnt/hgfs/vmsh/log/logtest/', '/mnt/hgfs/vmsh/ErrorCalculateResult.txt')
    calculate_error('/mnt/hgfs/vmsh/log/log2/', '/mnt/hgfs/vmsh/ErrorCalculateResult.txt')
    #calculate_error('/mnt/hgfs/vmsh/log/', '/mnt/hgfs/vmsh/ErrorCalculateResult.txt')
    print 'End'
