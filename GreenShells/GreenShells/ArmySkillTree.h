#pragma once

#include <string>

class ArmySkillTree
{
    bool Militia : 1;
    bool RangerT1 : 1;
    bool RangerT2 : 1;
    bool RangerT3 : 1;
    bool SwordT2 : 1;
    bool SwordT3 : 1;
    bool AxeT1 : 1;
    bool AxeT2 : 1;
    bool MaceT1 : 1;
    bool MaceT2 : 1;
    bool Fortress : 1;
    bool Shield : 1;
    bool Canon : 1;

public:
    ArmySkillTree();
    ArmySkillTree(std::string value);
    ArmySkillTree GetReadyForResearch();
    std::string toString();
};