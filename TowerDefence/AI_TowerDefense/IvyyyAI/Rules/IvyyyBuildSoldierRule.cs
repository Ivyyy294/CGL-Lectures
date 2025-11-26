using AI_Strategy;
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
            m_axis.Add(new IvyyyRuleAxis("CanBuySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 100f, 0f, 0f)));
            
            //Prevents soldiers from being spawn during place tower phase
            m_axis.Add(new IvyyyRuleAxis("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));

            //Caps the amount of soldier rows to AttackLane depth
            m_axis.Add(new IvyyyRuleAxis("LaneRowCounter", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 100f, 1f, 0f)));
            
            //Reduces the score for an AttackLane according to the tower density
            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerHp", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 200f, -0.15f, 1f, 0.5f)));

            //Reduces the score for AttackLanes with fewer soldiers per row
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.4f, 2f, 1f, 1f)));

            //Reduces the score if the ratio of enemy towers to soldiers per regiment is unfavorable
            m_axis.Add(new IvyyyRuleAxis("LaneSuccessFactor", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 500f, 1f, 0f, 0.6f)));
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
