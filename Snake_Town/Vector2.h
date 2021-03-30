#ifndef VECTOR2_H
#define VECTOR2_H


class Vector2
{
private:
	int m_x; //x component of Vector
	int m_y; //y component of Vector

public:
	Vector2 (); //default constructor
	Vector2 ( int x, int y ); //constructor, takes x and y values


	//operators used to add, subtract & divide
	Vector2 operator + ( const Vector2 & vect );
	Vector2 operator - ( const  Vector2 & vect );

	Vector2 operator / ( int val );

	bool operator==( Vector2 vect );


	//getters / setters
	int X () const {
		return m_x;
	}
	void X ( int val ) {
		m_x = val;
	}

	int Y () const {
		return m_y;
	}
	void Y ( int val ) {
		m_y = val;
	}
};

#endif // VECTOR2_H