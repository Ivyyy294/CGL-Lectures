using GameFramework;

namespace IvyyyAI
{
    public class IvyyyBuildSoldierRule : IvyyyRule
    {
        public IvyyyBuildSoldierRule(IvyyyWorldState state) : base(state)
        {
            m_target = "AttackLanes";
            m_axis.Add(new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 4f, 0.0f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("CanBuySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));

            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerHp", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.25f, 2f, 0.75f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerInReach", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.05f, 2f, 0.95f, 1f)));
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.25f, 2f, 0.75f, 1f)));
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Soldier!");

            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            for (int i = 0; i < attackLane.Width; ++i)
            {
                int xPos = attackLane.StartIndex + i;
                m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos);
            }
        }
    }
}
