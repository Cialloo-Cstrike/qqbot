#ifndef MsgType_H_
#define MsgType_H_

enum MessageType 
{
    /*
    do nothing with null message
    */
    NULLMSG = 0,
    /*
    line1: 2
    line2: NEW SURF RECORD
    line3: server name
    ...
    */
    SURFWR = 2,
    /*
    line1: 3
    line2: finish map
    line3: server name
    ...
    */
    SURFFINISH = 3,
    /*
    line1: 4
    line2: NEW BHOP RECORD
    line3: server name
    ...
    */
    BHOPWR = 4,
    /*
    line1: 5
    line2: finish map
    line3: server name
    */
    BHOPFINISH = 5
};

#endif
