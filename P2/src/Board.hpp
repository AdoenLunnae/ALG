#ifndef _BOARD_HPP_
#define _BOARD_HPP_
    
class Board{
    private:
        int _size;
    public:
        inline Board(const int &size): _size(size){};
        inline int size() const{return _size;}
};

#endif