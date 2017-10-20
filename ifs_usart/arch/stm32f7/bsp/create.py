#!/usr/bin/python
# -*- coding: cp936 -*-
import datetime
print "File Name:"
File = raw_input()
print "Author Name:"
Name = raw_input()
print "Version:"
Version = raw_input()
print "brief :"
Brief = raw_input()

print "FILE:" + File + '\n'\
    + "Name:" + Name + '\n'\
    + "Version:" + Version + '\n'\
    + "Brief:" + Brief
Date = datetime.date.today()

f = file(File, 'w')

f.write('/**\n\
  ******************************************************************************\n'\
        + '  * @file    '\
        + File + '\n'\
        + '  * @author  '\
        + Name + '\n'\
        + '  * @version V'\
        + Version + '\n'\
        + '  * @date    '\
        + str(Date) + '\n'\
        + '  * @brief   '\
        + Brief + '\n'\
        + '  ******************************************************************************\n\
  * @modify\n\
  *\n\
  ******************************************************************************\n  */\n'\
        + '\n'\
'/******************************End Of File(INC)*********************************/')

f.write('\n')
f.write('\n')
f.close()
