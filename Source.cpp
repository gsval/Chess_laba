#include <iostream>
using namespace std;
//������������ ����� ������ � ��� ����.
enum TFigure_type { pawn, rook, knight, bishop, queen, king };//�����, �����, ����, ����, ��������, ������
enum TFigure_color { no_color, black, withe };//���� ������

class TCoord {
private:
    short int x;
    short int y;
public:
    void set_x(int _x) { if (_x > -2 && _x < 8) { x = _x; } };
    void set_y(int _y) { if (_y > -2 && _y < 8) { y = _y; } };
    bool operator==(const TCoord& tmp) {
        if (tmp.x == x && tmp.y == y)return true;
        return false;
    }
    short int get_x() { return x; };
    short int get_y() { return y; };
    TCoord(int _x, int _y){
        x = _x;
        y = _y;

    }
    TCoord() {}
};
//������ ���������, ���������� � ���� ����� ��������� � ������ add_coo�� �����rd(), ���� �� ���������
//��� ���������� x,y �� ����������� ���� ������� TCoord. ������ ����������� � ���� ���, �� ����� �� ��������.
//�� ������ ����� ��� ����� ������ ������� ���������� ����� ����������
class TCoordMass {
private:
    short int count;
    TCoord* mass;
public:
    void add_coord(TCoord& _tmp) { add_coord(_tmp.get_x(), _tmp.get_y()); }
    void add_coord(short int x, short int y) {
        TCoord* tmp_mass = new TCoord[count + 1];
        for (short int i = 0; i < count; i++) { tmp_mass[i] = mass[i]; }
        tmp_mass[count].set_x(x);
        tmp_mass[count].set_y(y);
        delete[] mass;
        mass = tmp_mass;
    }
    void print() {
        for (int i = 0; i < count; i++) {
            cout << "X: " << mass[i].get_x() << "Y: " << mass[i].get_y() << endl;
        }
    }
    TCoordMass() { mass = nullptr; count = 0; }
    TCoordMass(TCoordMass&) {}
    ~TCoordMass() { delete[] mass; }
};

//����� - ����� ������ ���� �����, ����� ��� ���� ����� ������� ��� ������ � ����� �������.
class TFigure {
protected:
    short int id;//���������� ����� ������ �� ���� (�� 0 �� 31). �������� � ������������ �����������.
    TFigure_type type;//��� ������ �������� � ������������ ����������� �������.
    TCoord coord;//���������� ������, ���� ������ ������� - (-1,-1)
    TFigure_color color;//���� ������
};

//����� ����
class TKnight :public TFigure {// ������������ 
public:
   
    ~TKnight() {};//����������

    TCoordMass& get_list_coord() ;//���������� ������ ���������, ���� ������ ����� ����������, ��������� ���������� ����� �� ����� �������.
    bool check_move(TCoord& coord_last) ;//���������� true ���� ������ ����� ������������� �� ���������� ����������.
    void move_to(TCoord& coord_last) ;//���������� ������ �� ���������� ���������� ��� ��������(������ ������ ���� ���� TCoord). 
};

void TKnight::move_to(TCoord& coord_last) {
    coord.set_x(coord_last.get_x());
    coord.set_y(coord_last.get_y());
}
bool TKnight::check_move(TCoord& coord_last) {
    if (TCoord(coord.get_y() - 2, coord.get_x() - 1) == coord_last) return true;
    if (TCoord(coord.get_y() - 2, coord.get_x() + 1) == coord_last) return true;
    if (TCoord(coord.get_y() - 1, coord.get_x() + 2) == coord_last) return true;
    if (TCoord(coord.get_y() + 1, coord.get_x() + 2) == coord_last) return true;
    if (TCoord(coord.get_y() - 2, coord.get_x() - 1) == coord_last) return true;
    if (TCoord(coord.get_y() - 1, coord.get_x() - 2) == coord_last) return true;
    if (TCoord(coord.get_y() + 1, coord.get_x() - 2) == coord_last) return true;
    if (TCoord(coord.get_y() + 2, coord.get_x() - 1) == coord_last) return true;
    if (TCoord(coord.get_y() + 2, coord.get_x() + 1) == coord_last) return true;
    return false;
   /* if ((abs(coord_last.get_x() - coord.get_x()) == 2) && (abs(coord_last.get_y() - coord.get_y()) == 1)) return true;
    if ((abs(coord_last.get_x() - coord.get_x() == 1) && (abs(coord_last.get_y() - coord.get_y() == 2)))) return true;
    else return 0;*/
};
//TCoordMass& TKnight::get_list_coord() {
//    TCoordMass mass;
//    for (int i = -1; i <= 1; i++) {
//        for (int j = -1; j <= 1; j++) {
//            if (i == 0 && j == 0)continue; else {
//                int tmp_x = coord.get_x() + i, tmp_y = coord.get_y() + j;
//                if (tmp_x >= 0 && tmp_x < 8 && tmp_y >= 0 && tmp_y < 8) { mass.add_coord(tmp_x, tmp_y); }
//            }
//        }
//
//    }
//    return mass;
//}
TCoordMass& TKnight::get_list_coord() {
    TCoordMass *mass = new TCoordMass;//������� ���������
    mass->add_coord(coord.get_y() - 2, coord.get_x() -   1);
    mass->add_coord(coord.get_y() - 2, coord.get_x() + 1);
    mass->add_coord(coord.get_y() - 1, coord.get_x() + 2);
    mass->add_coord(coord.get_y() + 1, coord.get_x() + 2);
    mass->add_coord(coord.get_y() - 1, coord.get_x() - 2);
    mass->add_coord(coord.get_y() +1, coord.get_x() -2);
    mass->add_coord(coord.get_y() + 2, coord.get_x() - 1);
    mass->add_coord(coord.get_y() + 2, coord.get_x() + 1);


    /*for (int i = -2; i <= 2; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            if (i == -1 || i == 1)
                continue;
            else {
                int tmp_x = coord.get_x() + i, tmp_y = coord.get_y() + j;
                int tmp_x2 = coord.get_x() + j, tmp_y2 = coord.get_y() + i;
                if (tmp_x >= 0 && tmp_x2 < 8 && tmp_y >= 0 && tmp_y2 < 8) { mass.add_coord(tmp_x, tmp_y); }
            }
        }

    }*/
    return *mass;
}
//����� �����
class TRook :public TFigure {// ������������ 
public:
   

    TCoordMass& get_list_coord() ;//���������� ������ ���������, ���� ������ ����� ����������, ��������� ���������� ����� �� ����� �������.
    bool check_move(TCoord& coord_last) ;//���������� true ���� ������ ����� ������������� �� ���������� ����������.
    void move_to(TCoord& coord_last) ;//���������� ������ �� ���������� ���������� ��� ��������(������ ������ ���� ���� TCoord). 
};

void  TRook::move_to(TCoord& coord_last) {
    coord.set_x(coord_last.get_x());
    coord.set_y(coord_last.get_y());
}
bool TRook::check_move(TCoord& coord_last) {
    if (coord_last.get_x() == coord.get_x() && (coord_last.get_y() > -1) && (coord_last.get_y() != coord.get_y())) return true;
    if (coord_last.get_y() == coord.get_y() && (coord_last.get_x() > -1) && (coord_last.get_x() != coord.get_x())) return true;
   /* if ((abs(coord_last.get_x() - coord.get_x()) == 0) && (abs(coord_last.get_y() - coord.get_y()) != 0)) return true;
    if ((abs(coord_last.get_x() - coord.get_x() != 0) && (abs(coord_last.get_y() - coord.get_y() == 0)))) return true;*/
    /*else return 0;*/
    else return false;
};
TCoordMass& TRook::get_list_coord() {
    TCoordMass* mass = new TCoordMass;
    for (int i = coord.get_y(); i <= 7; i++) {
        mass->add_coord(coord.get_x(), i);
    };
    for (int i = coord.get_y(); i >= 0; i--) {
        mass->add_coord(coord.get_x(), i);
    };
    for (int i = coord.get_x(); i <= 7; i++) {
        mass->add_coord(i, coord.get_y());
    };
    for (int i = coord.get_x(); i >= 0; i--) {
        mass->add_coord(i, coord.get_y());
    };

        /*or (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 0; j++) {
            if (i == 0 && j == 0)
                continue;
            else {
                int tmp_x = coord.get_x() + i, tmp_y = coord.get_y() + j;
                int tmp_x = coord.get_x() + j, tmp_y = coord.get_y() + i;
                if (tmp_x >= 0 && tmp_x < 8 && tmp_y >= 0 && tmp_y < 8) { mass.add_coord(tmp_x, tmp_y); }
            }
        }

    }*/
    return *mass;
}
void main() {}
