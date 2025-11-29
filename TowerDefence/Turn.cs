using GameFramework;
using System.Collections.Generic;

namespace AI_Strategy
{
    public class Turn : Tower
    {
        protected override List<Unit> SortTargetsInRange(List<Unit> targets)
        {
            targets.Sort((a, b) => a.Health.CompareTo(b.Health));
            return targets;
        }
    }
    
}