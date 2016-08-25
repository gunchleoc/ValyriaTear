------------------------------------------------------------------------------[[
-- Filename: arm_armor.lua
--
-- Description: This file contains the definitions of all arm armor.
-- Each armor has a unique integer identifier that is used
-- as its key in the armor table below. Armor IDs are unique not only among
-- each other, but among other inventory game objects as well (items, weapons,
-- other classes of armor, etc).
--
-- Object IDs 40,001 through 50,000 are reserved for arm armor. Do not break this
-- limit, because other value ranges correspond to other types of inventory objects.
--
-- Armor IDs do -not- need to be sequential. When you make a new armor, keep it
-- grouped with similar armor types (shields with shields, etc.) and keep a buffer of
-- space between group types. This way we won't get a mess of random arm armor all over
-- this file.
--
-- All armor entries need the following data to be defined:
-- {name}: Text that defines the name of the armor.
-- {description}: A brief description about the armor.
-- {icon}: The filepath to the image icon representing this armor.
-- {physical_defense}: The amount of physical defense that the armor provides.
-- {magical_defense}: The amount of magical defense that the armor casues.
-- {standard_price}: The standard asking price of this armor from merchants.
-- {usable_by}: A list of characters which may equip this armor,
-- {slots}: The number of slots available to equip shards on the armor.
-- {key_item}: Tells whether the item is a key item, preventing it from being consumed or sold.
------------------------------------------------------------------------------]]

-- All armor definitions are stored in this table
if (armor == nil) then
   armor = {}
end


-- -----------------------------------------------------------------------------
-- IDs 40,001 - 40,500 are reserved for shields
-- -----------------------------------------------------------------------------

armor[40001] = {
    name = vt_system.Translate("Prismatic Ring"),
    description = vt_system.Translate("A strange ring that protects the wearer from darkness."),
    icon = "data/inventory/armor/jewelry_ring_prismatic.png",
    physical_defense = 4,
    magical_defense = 3,
    standard_price = 180,
    usable_by = BRONANN + KALYA + THANIS + SYLVE,
    slots = 0,

    trade_conditions = {
        [0] = 40,    -- Drunes
        [3100] = 4,  -- Refined Slimy Material
        [3107] = 5,  -- Saurian Material
        [3102] = 5,  -- Insect Material
        [3116] = 1,  -- Orb
    },
}

armor[40011] = {
    name = vt_system.Translate("Wooden Shield"),
    description = vt_system.Translate("Robust wooden oak protects from all but the heaviest of assaults."),
    icon = "data/inventory/armor/wooden_shield.png",
    physical_defense = 2,
    magical_defense = 0,
    standard_price = 90,
    usable_by = BRONANN + KALYA + THANIS + SYLVE,
    slots = 0
}

armor[40012] = {
    name = vt_system.Translate("Metal Shield"),
    description = vt_system.Translate("A shield formed completely out of a light-weight but cheap metallic alloy."),
    icon = "data/inventory/armor/metal_shield.png",
    physical_defense = 5,
    magical_defense = 2,
    standard_price = 170,
    usable_by = BRONANN + THANIS,
    slots = 0
}

armor[40013] = {
    name = vt_system.Translate("Phoenix Shield"),
    description = vt_system.Translate("A tall steel shield with a mighty phoenix emblazoned on the front."),
    icon = "data/inventory/armor/phoenix_shield.png",
    physical_defense = 10,
    magical_defense = 6,
    standard_price = 310,
    usable_by = BRONANN + THANIS,
    slots = 0
}

armor[40014] = {
    name = vt_system.Translate("Trident Shield"),
    description = vt_system.Translate("A large shield with enough fortitude to withstand waves of powerful attacks."),
    icon = "data/inventory/armor/trident_shield.png",
    physical_defense = 10,
    magical_defense = 6,
    standard_price = 310,
    usable_by = BRONANN + THANIS,
    slots = 1
}

