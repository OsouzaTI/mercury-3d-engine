#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>


/*
	
	Library vectors

	Data  : 03/11/2020
	Author: Oz�ias Souza.
	License: MIT
*/

/*
__      __       _                   ___  _____
 \ \    / /      | |                 |__ \|  __ \
  \ \  / /__  ___| |_ ___  _ __ ___     ) | |  | |
   \ \/ / _ \/ __| __/ _ \| '__/ __|   / /| |  | |
	\  /  __/ (__| || (_) | |  \__ \  / /_| |__| |
	 \/ \___|\___|\__\___/|_|  |___/ |____|_____/
*/

template<typename T>
struct vect2 {
	T x;
	T y;

	vect2<T>(){}
	vect2<T>(T x, T y) {
		this->x = x;
		this->y = y;
	}

} ;

template<typename T>
struct vect3 {
	T x;
	T y;
	T z;
} ;

template<typename T>
struct vect4 {
	T x;
	T y;
	T z;
	T w;
} ;

template<typename T>
std::ostream& operator<< (std::ostream& os, vect2<T>& p) {
	os << "vector2D < x: " << p.x << " , " << "y: " << p.y << " >" << std::endl;
	return os;
}

template<typename T>
vect2<T> operator+(const vect2<T> u, const vect2<T> v) {
	return vect2<T>{
		u.x + v.x,
		u.y + v.y,
	};
}

template<typename T>
std::ostream& operator<< (std::ostream& os, vect3<T>& p) {
	os << "vector3D <" << p.x << "," << p.y << "," << p.z << ">" << std::endl;
	return os;
}


template<typename T>
vect3<T> operator+(const vect3<T> u, const vect3<T> v) {
	return vect3<T>{
		u.x + v.x,
		u.y + v.y,
		u.z + v.z,
	};
}

template<typename T>
vect2<T> operator-(const vect2<T> u, const vect2<T> v) {
	return vect2<T>{
		u.x - v.x,
		u.y - v.y,
	};
}

template<typename T>
vect2<T> operator-(const vect2<T> u, T s) {
	return vect2<T>{
		u.x - s,
		u.y - s,
	};
}

template<typename T>
vect2<T> operator*(T s, const vect2<T> u) {
	return vect2<T>{
		s * u.x,
		s * u.y,
	};
}



template<typename T> vect2<T> smultvect(vect2<T> &u, T s) {
	return vect2<T>{
		u.x * s,
		u.y * s
	};
}

template<typename T> vect2<T> vmultvect(vect2<T> &u, vect2<T> &v) {
	return vect2<T>{
		u.x * v.x,
		u.y * v.y
	};
}

template<typename T> vect2<T> vsumvect(vect2<T> &u, vect2<T> &v) {
	return vect2<T>{
		u.x + v.x,
		u.y + v.y
	};
}

template<typename T> vect2<T> arotvectx(vect2<T> &u, T a) {
	return vect2<T>{
		u.x * cosf(a) - u.y * sinf(a),
		u.x * sinf(a) + u.y * cosf(a)
	};
}

template<typename T> vect2<T> projection2d(vect3<T> &u) {
	return vect2<T>{
		u.x,
		u.y
	};
}

template<typename T> float vlenght(vect2<T> &u) {
	return sqrtf(u.x * u.x + u.y * u.y);
}

template<typename T> float distance_to_point(vect2<T> &u, vect2<T> &v) {
	float a = powf(v.x - u.x, 2.0f);
	float b = powf(v.y - u.y, 2.0f);
	return sqrtf(a + b);
}

template<typename T> void vnormalize(vect2<T>* u) {
	float lenght = vlenght(*u);
	u->x /= lenght;
	u->y /= lenght;
}

/*
__      __       _                   ____  _____
 \ \    / /      | |                 |___ \|  __ \
  \ \  / /__  ___| |_ ___  _ __ ___    __) | |  | |
   \ \/ / _ \/ __| __/ _ \| '__/ __|  |__ <| |  | |
	\  /  __/ (__| || (_) | |  \__ \  ___) | |__| |
	 \/ \___|\___|\__\___/|_|  |___/ |____/|_____/
====================================================================

	Abaixo est�o as fun��es de opera��es com vetores
	no espa�o r3.

	A estrutura basica de um vetor de 3 componentes
	� a seguinte:

	Vect3 u<int>{ 0, 0, 10 };

	Pode ser acessado das seguintes formas:
		Forma de indices:
			u[0] -> Componente x
			u[1] -> Componente y
			u[2] -> Componente z
		Forma de estruturas
			u.x -> Componente x
			u.y -> Componente y
			u.z -> Componente z

====================================================================
*/


template<typename T> vect3<T> smultvect(vect3<T> &u, T s) {
	return vect3<T>{
		u.x* s,
		u.y* s,
		u.z* s
	};
}


template<typename T> vect3<T> vmultvect(vect3<T> &u, vect3<T> &v) {
	return vect3<T>{
		u.x * v.x,
		u.y * v.y,
		u.z * v.z
	};
}

template<typename T> void stransvect(vect3<T> &u, T s) {
	u.x + s;
	u.y + s;
	u.z + s;
}

template<typename T> vect3<T> vsubvect(vect3<T> &u, vect3<T> &v) {
	return vect3<T>{
		u.x - v.x,
		u.y - v.y,
		u.z - v.z,
	};
}

template<typename T> vect3<T> vcrossvect(vect3<T> &u, vect3<T> &v) {
	return vect3<T>{
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	};
}

template<typename T> T vdotvect(vect3<T> &u, vect3<T> &v) {
	return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}



template<typename T> vect3<T> arotvectx(vect3<T> &u, float a) {
	return vect3<T>{
		u.x,
		u.y * cosf(a) - u.z * sinf(a),
		u.y * sinf(a) + u.z * cosf(a)
	};
}

template<typename T> vect3<T> arotvecty(vect3<T> &u, float a) {
	return vect3<T>{
		u.x* cosf(a) - u.z * sinf(a),
		u.y,
		u.x * sinf(a) + u.z * cosf(a)
	};
}

template<typename T> vect3<T> arotvectz(vect3<T> &u, float a) {
	return vect3<T>{
		u.x * cosf(a) - u.y * sinf(a),
		u.x * sinf(a) + u.y * cosf(a),
		u.z
	};
}

/// Proje��es a serem trabalhadas 

template<typename T> vect3<T> pvprojection(vect3<T> &u, float d) {
	if (u.z != 0) {
		return vect3<T>{
			u.x / (u.z / d),
			u.y / (u.z / d),
			1 - (d / u.z)
		};
	}
}

template<typename T> vect3<T> spvprojection(vect3<T> &u, float camz) {
	u.z -= camz;
	if (u.z != 0) {
		return vect3<T>{
			u.x / u.z,
			u.y / u.z,
			u.z
		};
	}
}

template<typename T> vect2<T> ovprojection(vect3<T> &u) {
	return vect2<T>{
		u.x,
		u.y
	};
}

template<typename T> vect2<T> ovprojection(vect4<T> &u) {
	return vect2<T>{
		u.x,
		u.y
	};
}

template<typename T> T vlenght(vect3<T>& u) {
	return sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
}

template<typename T> void vnormalize(vect3<T>* u) {
	float lenght = vlenght<T>(*u);
	u->x /= lenght;
	u->y /= lenght;
	u->z /= lenght;
}

template<typename T> vect3<T> vec3_from_vec4(vect4<T> &u) {
	return vect3<T>{
		u.x,
		u.y,
		u.z
	};
}

/*
__      __       _                   _  _   _____
 \ \    / /      | |                 | || | |  __ \
  \ \  / /__  ___| |_ ___  _ __ ___  | || |_| |  | |
   \ \/ / _ \/ __| __/ _ \| '__/ __| |__   _| |  | |
	\  /  __/ (__| || (_) | |  \__ \    | | | |__| |
	 \/ \___|\___|\__\___/|_|  |___/    |_| |_____/
*/

// vec4
template<typename T> vect4<T> vec4_from_vec3(vect3<T>& u) {
	return vect4<T>{
		u.x,
		u.y,
		u.z,
		1
	};
}

template<typename T> vect4<T> smultvect(vect4<T> &u, T s) {
	return vect4<T>{
		u.x* s,
		u.y* s,
		u.z* s,
		1
	};
}

#endif // !VECTOR_H