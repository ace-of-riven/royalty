#pragma once

#include "../ext_include.h"

#include "eng_component.h"

#include <vector>
#include <map>

class Bone {
	glm::mat4 OffsetMatrix;
	glm::mat4 TransformMatrix;

	std::string Name;
	int ID;
public:
	Bone ( const std::string& name , int ID , const glm::mat4& offset );
	~Bone ( );

	inline int GetID ( ) const { return ID; }
	inline const std::string& GetName ( ) const { return Name; }
	inline const glm::mat4 &GetMatrix ( ) const { return OffsetMatrix * TransformMatrix ; }
};

class Skeleton : public Component {
	std::map<int , Bone *> BoneInfo_i;
	std::map<std::string , Bone *> BoneInfo_s;
public:
	Skeleton ( );
	~Skeleton ( );

	Bone *CreateBone ( const std::string &name , const glm::mat4 &offset );

	Bone *GetBone_ensure ( const std::string &name , const glm::mat4 &offset );

	const Bone *GetBone ( const std::string &name ) const;
	Bone *GetBone ( const std::string &name );

	const Bone *GetBone ( int id ) const;
	Bone *GetBone ( int id );

	inline int GetBoneCount ( ) const { return BoneInfo_i.size ( ); }
};
