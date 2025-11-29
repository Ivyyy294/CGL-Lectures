using GameFramework;

namespace IvyyyAI
{
    public class IvyyyBuildSoldierRule : IvyyyRule
    {
        public IvyyyBuildSoldierRule(IvyyyWorldState state) : base(state)
        {
            m_weight = 1f;
            m_target = "AttackLanes";

            //Not having enough gold to build a complete row reduces score significant
            m_axis.Add(new IvyyyRuleAxis("CanBuySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
            
            //Prevents soldiers from being spawn during place tower phase
            m_axis.Add(new IvyyyRuleAxis("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));

            //Favors lanes with higher soldier count
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.1f, 2f, 1f, 1f)));
            
            m_axis.Add(new IvyyyRuleAxis("LaneSuccessFactor", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -6f, 4f, 1f, 0.6f)));
        }

        //Build row of soldiers with given with and start index
        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Soldier!");

            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            for (int i = 0; i < attackLane.Width; ++i)
            {
                int xPos = attackLane.StartIndex + i;
                if (m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos) == Player.SoldierPlacementResult.Success)
                {
                    //Pass standy depth to soldiers
                    IvyyySoldier soldier = (IvyyySoldier)m_worldState.Player.EnemyLane.GetCellAt(xPos, 0).Unit;
                    soldier.Depth = attackLane.Depth;
                }
            }

            m_worldState.RowCounter++;
        }
    }
}
