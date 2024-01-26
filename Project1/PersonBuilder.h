#pragma once
#include "PrimitiveObject.h"
#include "PrimitiveBuilder.h"
#include <vector>

/// <summary>
/// creates the animations for the person walking
/// </summary>
/// <returns>a vecotr of animations where 0-1 are the arms 2-3</returns>
static vector<Animation> create_swing_animations(bool reversed = false, glm::vec3 pivot = {}, float totalRotation = 45) {
    vector<Animation> animations(2);
    float time = 1;

    if (reversed) {
        totalRotation = -totalRotation;
    }

    //set the initial delta_position of the swing
    Keyframe init = Keyframe(glm::vec4(1, 0, 0, -totalRotation / 2), time /2, pivot);

    //do the actual swing
    vector<Keyframe> swing = {
        Keyframe(glm::vec4(1, 0, 0, totalRotation), time , pivot),
        Keyframe(glm::vec4(1, 0, 0, -totalRotation), time, pivot)
    };

    Animation start_swing = Animation(init);
    Animation Swing = Animation(swing, true);

    animations[0] = start_swing;
    animations[1] = Swing;

    return animations;
}

static Animation create_forward_animation(glm::vec3 movement = {0,0,1}) {
    Keyframe frame = Keyframe(movement, 1);

    Animation animation;
    animation.AddKeyframe(frame);
    return animation;
}

static Animation Create_flip_animation(glm::vec4 rotation = {0,1,0, 180}, float time = 1) {
    
    Keyframe flip = Keyframe(rotation, time);
    Keyframe wait = Keyframe(1);

    vector<Keyframe> flips = {
        flip,
        wait,
        flip,
        wait,
        flip,
        wait,
        flip,
        wait,
        flip,
        wait,
        flip
    };

    return Animation(flips);
}

//just to clarify this animation could be done in a single animation, however i felt this would be easier
static Animation create_forward_turn_back_animation(glm::vec3 movement = {0,0,1}, float time = 1, float flipTime = 1) {
    const float flip_angle = 180;

    vector<Keyframe> frames(4);

    Keyframe flip = Keyframe(glm::vec4(0,1,0, flip_angle), flipTime);

    Keyframe move_forward = Keyframe(movement, time);
    Keyframe move_backward = Keyframe(-movement, time);

    frames[0] = move_forward;
    frames[1] = flip;
    frames[2] = move_backward;
    frames[3] = flip;

    return Animation(frames, true);
}

static PrimitiveObject* CreatePerson() {

    const int mesh_ammount = 6;
    const glm::vec3 skin_color = glm::vec3(0.68f, 0.59f, 0.49f);
    const glm::vec3 jean_color = glm::vec3(0.42f, 0.43f, 0.91f);
    const glm::vec3 shirt_color = glm::vec3(0.256f, 0.161f, 0.156f);
    const float torsoSize = 1;

    const float armSize = 0.15;
    const float armheigth = 1.1f;

    const float legSize = 0.2f;
    const float legHeight = 1.5f;


#pragma region Create meshes

    PrimitiveMesh* meshes = new PrimitiveMesh[mesh_ammount]{
        *CreateSolidRect(legHeight, legSize, legSize, jean_color), //legs
        *CreateSolidRect(legHeight, legSize, legSize, jean_color),

        *CreateSolidRect(armheigth, armSize, armSize, skin_color), //arms
        *CreateSolidRect(armheigth, armSize, armSize, skin_color),

        *CreateSphere(0.4f, 20, 20, skin_color), //head

        *CreateSolidRect(torsoSize,torsoSize, torsoSize * 0.5f, shirt_color), //body
    };

#pragma endregion



#pragma region Set meshe locations

    meshes[0].Move(torsoSize * 0.25f, -torsoSize, legSize * (torsoSize * 0.5f)); //legs
    meshes[1].Move(torsoSize * -0.25f, -torsoSize, legSize * (torsoSize * 0.5f));
    
    meshes[2].Move(torsoSize * 0.5f + armSize * 0.5f, 0, 0); //arms
    meshes[2].Rotate(0, 1, 0, 180);

    meshes[3].Move(torsoSize * -0.5f - armSize * 0.5f, 0, 0); 
    meshes[3].Rotate(0, 1, 0, 180);

    meshes[4].Move(0, 0.75f, 0); //head

#pragma endregion


#pragma region Animations

    vector<Animation> leg_animations_1 = create_swing_animations(false, {0,legHeight/2, 0});
    vector<Animation> leg_animations_2 = create_swing_animations(true, {0, legHeight/2, 0});

    vector<Animation> arm_animations_1 = create_swing_animations(false, {0,armheigth/2, 0});
    vector<Animation> arm_animations_2 = create_swing_animations(true, {0,armheigth/2, 0});

    meshes[0].setAnimations(leg_animations_1);
    meshes[1].setAnimations(leg_animations_2);

    meshes[2].setAnimations(arm_animations_1);
    meshes[3].setAnimations(arm_animations_2);
    //create_forward_turn_back_animation();

    Animation person_movement = Create_flip_animation(glm::vec4(0,1,0, 180), 1);//create_forward_turn_back_animation({0,0,5}, 2, 1);

#pragma endregion

    PrimitiveObject* person = new PrimitiveObject(meshes, mesh_ammount);
    person->Move(0, 0, 3);  
    person->setAnimation(person_movement);

    return person;
}