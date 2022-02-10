#include "../eng_skeleton.h"

Bone::Bone ( const std::string &name , int ID , const glm::mat4 &offset ) : Name ( name ) , ID ( ID ) , OffsetMatrix ( offset ) {
	TransformMatrix = glm::inverse ( offset ) ;
}
Bone::~Bone ( ) {
}

//

Skeleton::Skeleton ( ) : Component ( COMP_SKELETON ) {

}

Skeleton::~Skeleton ( ) {
	for ( auto bone : BoneInfo_i )
		delete bone.second;
}

Bone *Skeleton::CreateBone ( const std::string &name , const glm::mat4 &offset ) {
	assert ( GetBone ( name ) == NULL ) ;

	int free_id = BoneInfo_i.size ( );

	Bone *bone = new Bone ( name , free_id , offset );
	BoneInfo_i [ free_id ] = bone;
	BoneInfo_s [ name ] = bone;
	return bone;
}

Bone *Skeleton::GetBone_ensure ( const std::string &name , const glm::mat4 &offset ) {
	Bone *found = GetBone ( name );
	if ( found == NULL )
		return CreateBone ( name , offset ) ;
	return found;
}

const Bone *Skeleton::GetBone ( const std::string &name ) const {
	auto bone_itr = BoneInfo_s.find ( name );
	if ( bone_itr == BoneInfo_s.end ( ) )
		return NULL;
	return bone_itr->second;
}

Bone *Skeleton::GetBone ( const std::string &name ) {
	auto bone_itr = BoneInfo_s.find ( name );
	if ( bone_itr == BoneInfo_s.end ( ) )
		return NULL;
	return bone_itr->second;
}

const Bone *Skeleton::GetBone ( int id ) const {
	auto bone_itr = BoneInfo_i.find ( id );
	if ( bone_itr == BoneInfo_i.end ( ) )
		return NULL;
	return bone_itr->second;
}

Bone *Skeleton::GetBone ( int id ) {
	auto bone_itr = BoneInfo_i.find ( id );
	if ( bone_itr == BoneInfo_i.end ( ) )
		return NULL;
	return bone_itr->second;
}
