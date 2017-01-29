////////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2004-2011 by The Allacrost Project
//            Copyright (C) 2012-2016 by Bertram (Valyria Tear)
//                         All Rights Reserved
//
// This code is licensed under the GNU GPL version 2. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.gnu.org/copyleft/gpl.html for details.
////////////////////////////////////////////////////////////////////////////////

/** ****************************************************************************
*** \file    global_objects.h
*** \author  Tyler Olsen, roots@allacrost.org
*** \author  Yohann Ferreira, yohann ferreira orange fr
*** \brief   Header file for global game objects
***
*** This file contains several representations of inventory "objects" used
*** throughout the game. Objects include items, weapons, armor, etc.
*** ***************************************************************************/

#ifndef __GLOBAL_OBJECTS_HEADER__
#define __GLOBAL_OBJECTS_HEADER__

#include "global_utils.h"

#include "engine/video/image.h"
#include "engine/script/script.h"

#include "utils/ustring.h"

namespace vt_script {
class ReadScriptDescriptor;
}

namespace vt_global
{

class GlobalSpirit;

/** ****************************************************************************
*** \brief An abstract base class for representing a game object
***
*** All game objects inherit from this class. This allows objects of all types to
*** be stored in the same container (an inventory list for instance) and promotes
*** efficient code reuse for all game objects. The class is designed so that a
*** single class object can represent multiple instances of the same game object.
*** In other words, you can represent 50 healing potions with a single GlobalObject
*** class object rather than having to create and managed 50 class objects, one for
*** each potion. The _count member achieves this convenient function.
***
*** A GlobalObject with an ID value of zero is considered invalid. Most of the
*** protected members of this class can only be set by the constructors or methods
*** of deriving classes.
***
*** \note The price of an object is not actually the price it is bought or sold
*** at in the game. It is a "base price" from which all levels of buy and sell
*** prices are derived from.
***
*** \todo The "lore" for an object is a feature that we have discussed but not
*** yet decided if we wish to implement. Placeholders exist in this class for now,
*** but if lore is not to be implemented as a game feature they should be removed.
*** ***************************************************************************/
class GlobalObject
{
public:
    GlobalObject() :
        _id(0),
        _is_key_item(false),
        _count(0),
        _price(0),
        _trade_price(0)
    {
    }

    explicit GlobalObject(uint32_t id, uint32_t count = 1) :
        _id(id),
        _is_key_item(false),
        _count(count),
        _price(0),
        _trade_price(0)
    {
    }

    virtual ~GlobalObject()
    {
    }

    //! \brief Returns true if the object is properly initialized and ready to be used
    bool IsValid() const {
        return (_id != 0);
    }

    //! \brief Returns true if the object is properly initialized and ready to be used
    bool IsKeyItem() const {
        return _is_key_item;
    }

    /** \brief Purely virtual function used to distinguish between object types
    *** \return A value that represents the type of object
    **/
    virtual GLOBAL_OBJECT GetObjectType() const = 0;

    /** \brief Increments the number of objects represented by this class
    *** \param count The count increment value (default value == 1)
    **/
    void IncrementCount(uint32_t count = 1) {
        _count += count;
    }

    /** \brief Decrements the number of objects represented by this class
    *** \param count The count decrement value (default value == 1)
    *** \note When the count reaches zero, this class object does <i>not</i> self-destruct. It is the user's
    *** responsiblity to check if the count becomes zero, and to destroy the object if it is appropriate to do so.
    **/
    void DecrementCount(uint32_t count = 1) {
        if(count > _count) _count = 0;
        else _count -= count;
    }

    //! \name Class Member Access Functions
    //@{
    uint32_t GetID() const {
        return _id;
    }

    const vt_utils::ustring &GetName() const {
        return _name;
    }

    const vt_utils::ustring &GetDescription() const {
        return _description;
    }

    void SetCount(uint32_t count) {
        _count = count;
    }

    uint32_t GetCount() const {
        return _count;
    }

    uint32_t GetPrice() const {
        return _price;
    }

    uint32_t GetTradingPrice() const {
        return _trade_price;
    }

    const std::vector<std::pair<uint32_t, uint32_t> >& GetTradeConditions() const {
        return _trade_conditions;
    }

    const vt_video::StillImage& GetIconImage() const {
        return _icon_image;
    }

    const std::vector<std::pair<GLOBAL_STATUS, GLOBAL_INTENSITY> >& GetStatusEffects() const {
        return _status_effects;
    }
    //@}

protected:
    /** \brief An identification number for each unique item
    *** \note An ID number of zero indicates an invalid object
    **/
    uint32_t _id;

    //! \brief The name of the object as it would be displayed on a screen
    vt_utils::ustring _name;

    //! \brief A short description of the item to display on the screen
    vt_utils::ustring _description;

    //! \brief Tells whether an item is a key item, preventing from being consumed or sold.
    bool _is_key_item;

    //! \brief Retains how many occurences of the object are represented by this class object instance
    uint32_t _count;

    //! \brief The base price of the object for purchase/sale in the game
    uint32_t _price;

    //! \brief The additional price of the object requested when trading it.
    uint32_t _trade_price;

    //! \brief The trade conditions of the item <item_id, number>
    //! There is an exception: If the item_id is zero, the second value is the trade price.
    std::vector<std::pair<uint32_t, uint32_t> > _trade_conditions;

    //! \brief A loaded icon image of the object at its original size of 60x60 pixels
    vt_video::StillImage _icon_image;

    /** \brief Container that holds the intensity of each type of status effect of the object
    *** Effects with an intensity of GLOBAL_INTENSITY_NEUTRAL indicate no status effect bonus
    **/
    std::vector<std::pair<GLOBAL_STATUS, GLOBAL_INTENSITY> > _status_effects;

    //! \brief The skills that can be learned when equipping that piece of equipment.
    std::vector<uint32_t> _equipment_skills;

    //! \brief Causes the object to become invalid due to a loading error or other significant issue
    void _InvalidateObject() {
        _id = 0;
    }

    /** \brief Reads object data from an open script file
    *** \param script A reference to a script file that has been opened and prepared
    ***
    *** This method does not do any of its own error case checking. Only derived classes may call this
    *** protected function and they are expected to have the script file successfully opened and the correct
    *** table context prepared. This function will do nothing more but read the expected key/values of
    *** the open table in the script file and return.
    **/
    void _LoadObjectData(vt_script::ReadScriptDescriptor &script);

    //! \brief Loads status effects data
    void _LoadStatusEffects(vt_script::ReadScriptDescriptor &script);

    //! \brief Loads trading conditions data
    void _LoadTradeConditions(vt_script::ReadScriptDescriptor &script);

    //! \brief Loads the object linked skills (used by equipment only)
    void _LoadEquipmentSkills(vt_script::ReadScriptDescriptor &script);
}; // class GlobalObject


/** ****************************************************************************
*** \brief Represents items used throughout the game
***
*** This class is for general use items such as healing potions. Each item has a
*** different effect when it is used, implemented by a Lua function written
*** specifically for the item which calls it. Some items may be used only in certain
*** scenarios (in battles, on the field, etc.). All items may be used by any
*** character or enemy in the game.
*** ***************************************************************************/
class GlobalItem : public GlobalObject
{
public:
    /** \param id The unique ID number of the item
    *** \param count The number of items to initialize this class object as representing (default value == 1)
    **/
    explicit GlobalItem(uint32_t id, uint32_t count = 1);
    virtual ~GlobalItem() override
    {
    }

    GlobalItem(const GlobalItem& copy);
    GlobalItem& operator=(const GlobalItem& copy);

    GLOBAL_OBJECT GetObjectType() const {
        return GLOBAL_OBJECT_ITEM;
    }

    //! \brief Returns true if the item can be used in battle
    bool IsUsableInBattle() const {
        return _battle_use_function.is_valid();
    }

    //! \brief Returns true if the item can be used in the field
    bool IsUsableInField() const {
        return _field_use_function.is_valid();
    }

    //! \name Class Member Access Functions
    //@{
    GLOBAL_TARGET GetTargetType() const {
        return _target_type;
    }

    /** \brief Returns a pointer to the luabind::object of the battle use function
    *** \note This function will return nullptr if the skill is not usable in battle
    **/
    const luabind::object& GetBattleUseFunction() const {
        return _battle_use_function;
    }

    /** \brief Returns a pointer to the luabind::object of the field use function
    *** \note This function will return nullptr if the skill is not usable in the field
    **/
    const luabind::object& GetFieldUseFunction() const {
        return _field_use_function;
    }

    //! \brief Returns Warmup time needed before using this item in battles.
    inline uint32_t GetWarmUpTime() const {
        return _warmup_time;
    }

    //! \brief Returns Warmup time needed before using this item in battles.
    inline uint32_t GetCoolDownTime() const {
        return _cooldown_time;
    }

    /** \brief Tells the animation script filename linked to the skill for the given character,
    *** Or an empty value otherwise;
    **/
    std::string GetAnimationScript(uint32_t character_id) const;
    //@}

private:
    //! \brief The type of target for the item
    GLOBAL_TARGET _target_type;

    //! \brief A reference to the script function that performs the item's effect while in battle
    luabind::object _battle_use_function;

    //! \brief A reference to the script function that performs the item's effect while in a menu
    luabind::object _field_use_function;

    //! \brief The warmup time in milliseconds needed before using this item in battles.
    uint32_t _warmup_time;

    //! \brief The cooldown time in milliseconds needed after using this item in battles.
    uint32_t _cooldown_time;

    //! \brief map containing the animation scripts names linked to each characters id for the given skill.
    std::map <uint32_t, std::string> _animation_scripts;
}; // class GlobalItem : public GlobalObject


/** ****************************************************************************
*** \brief Represents weapon that may be equipped by characters or enemies
***
*** All classes of weapons (swords, bows, spears, etc.) are represented by this
*** class. Typically, a weapon may only be used by a select few and can not be
*** equipped on every character. Weapons have two attack ratings: physical
*** and magical, both of which are included in the damage calculation
*** formulae when a character or enemy attacks using the weapon. Weapons may also
*** have a small number of slots in which spirits can be merged to improve
*** or alter the weapon's properties. Some weapons have zero sockets available.
*** Finally, weapons may come imbued with certain elemental or status effect
*** properties that are inflicted on a target.
*** ***************************************************************************/
class GlobalWeapon : public GlobalObject
{
public:
    /** \param id The unique ID number of the weapon
    *** \param count The number of weapons to initialize this class object as representing (default value == 1)
    **/
    explicit GlobalWeapon(uint32_t id, uint32_t count = 1);
    virtual ~GlobalWeapon() override
    {
    }

    GLOBAL_OBJECT GetObjectType() const {
        return GLOBAL_OBJECT_WEAPON;
    }

    //! \name Class Member Access Functions
    //@{
    uint32_t GetPhysicalAttack() const {
        return _physical_attack;
    }

    uint32_t GetMagicalAttack() const {
        return _magical_attack;
    }

    uint32_t GetUsableBy() const {
        return _usable_by;
    }

    const std::vector<GlobalSpirit *>& GetSpiritSlots() const {
        return _spirit_slots;
    }

    const std::string& GetAmmoAnimationFile() const {
        return _ammo_animation_file;
    }

    //! \brief Get the animation filename corresponding to the character weapon animation
    //! requested.
    const std::string& GetWeaponAnimationFile(uint32_t character_id, const std::string& animation_alias);

    //! \brief Gives the list of learned skill thanks to this piece of equipment.
    const std::vector<uint32_t>& GetEquipmentSkills() const {
        return _equipment_skills;
    }
    //@}

private:
    //! \brief The battle image animation file used to display the weapon ammo.
    std::string _ammo_animation_file;

    //! \brief The amount of physical damage that the weapon causes
    uint32_t _physical_attack;

    //! \brief The amount of magical damage that the weapon causes for each elements.
    uint32_t _magical_attack;

    /** \brief A bit-mask that determines which characters can use or equip the object
    *** See the game character ID constants in global_actors.h for more information
    **/
    uint32_t _usable_by;

    //! \brief The info about weapon animations for each global character.
    //! map < character_id, map < animation alias, animation filename > >
    std::map <uint32_t, std::map<std::string, std::string> > _weapon_animations;

    /** \brief Spirit slots which may be used to place spirits on the weapon
    *** Weapons may have no slots, so it is not uncommon for the size of this vector to be zero.
    *** When spirit slots are available but empty (has no attached spirit), the pointer at that index
    *** will be nullptr.
    **/
    std::vector<GlobalSpirit *> _spirit_slots;

    //! \brief Loads the battle animations data for each character that can use the weapon.
    void _LoadWeaponBattleAnimations(vt_script::ReadScriptDescriptor& script);
}; // class GlobalWeapon : public GlobalObject


/** ****************************************************************************
*** \brief Represents all types of armor that may be equipped on characters and enemies
***
*** There are actually four types of armor: head, torso, arm, and leg. However all
*** four types are represented by this single class. The only functional difference
*** between different types of armor is where they may be equipped on an actor. Not
*** all armor can be equipped by any character or enemy. Typically, armor may only
*** be used by a select few and can not be equipped on every character. Armor have
*** two defense ratings: physical and magical, both of which are included in
*** the damage calculation formulae when a character or enemy is attacked at the
*** location where the armor is equipped. Armor may also have a small number of
*** "sockets" in which spirits can be inserted to improve or alter the armor's
*** properties. Some armor will have zero sockets available. Finally, armor may
*** come imbued with certain elemental or status effect properties that bolster
*** and protect the user.
*** ***************************************************************************/
class GlobalArmor : public GlobalObject
{
public:
    explicit GlobalArmor(uint32_t id, uint32_t count = 1);
    virtual ~GlobalArmor() override
    {
    }

    //! \brief Returns the approriate armor type (head, torso, arm, leg) depending on the object ID
    GLOBAL_OBJECT GetObjectType() const;

    uint32_t GetPhysicalDefense() const {
        return _physical_defense;
    }

    uint32_t GetMagicalDefense() const {
        return _magical_defense;
    }

    uint32_t GetUsableBy() const {
        return _usable_by;
    }

    const std::vector<GlobalSpirit *>& GetSpiritSlots() const {
        return _spirit_slots;
    }

    //! \brief Gives the list of learned skill thanks to this piece of equipment.
    const std::vector<uint32_t>& GetEquipmentSkills() const {
        return _equipment_skills;
    }

private:
    //! \brief The amount of physical defense that the armor provides
    uint32_t _physical_defense;

    //! \brief The amount of magical defense that the armor provides against each elements
    uint32_t _magical_defense;

    /** \brief A bit-mask that determines which characters can use or equip the object
    *** See the game character ID constants in global_actors.h for more information
    **/
    uint32_t _usable_by;

    /** \brief Sockets which may be used to place spirits on the armor
    *** Armor may have no sockets, so it is not uncommon for the size of this vector to be zero.
    *** When a socket is available but empty (has no attached spirit), the pointer at that index
    *** will be nullptr.
    **/
    std::vector<GlobalSpirit *> _spirit_slots;
}; // class GlobalArmor : public GlobalObject


/** ****************************************************************************
*** \brief Represents any type of spirit that can be attached to weapons and armor
***
*** Spirits are small gems or stones that can be placed into sockets available on
*** weapons and armor. Spirits have the ability to enhance the properties of
*** equipment it is attached to, allowing the player a degree of customization
*** in the weapons and armor that their character use.
***
*** \todo This class is not yet implemented
*** ***************************************************************************/
class GlobalSpirit : public GlobalObject
{
public:
    explicit GlobalSpirit(uint32_t id, uint32_t count = 1);
    virtual ~GlobalSpirit() override
    {
    }

    GLOBAL_OBJECT GetObjectType() const {
        return GLOBAL_OBJECT_SPIRIT;
    }
}; // class GlobalSpirit : public GlobalObject

} // namespace vt_global

#endif // __GLOBAL_OBJECTS_HEADER__
