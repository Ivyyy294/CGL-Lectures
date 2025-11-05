using GameFramework;

namespace IvyyyAI
{
    public class IvyyyBuildSoldierRule : IvyyyRule
    {
        public IvyyyBuildSoldierRule(IvyyyState state) : base(state)
        {
            m_target = "AttackLanes";
            m_axis.Add(new IvyyyRuleAxis("GoldCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.75f, 1f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.5f, 1f, 0.5f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));

            m_axis.Add(new IvyyyRuleAxis("LaneEnemyTowerHp", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 1f, 1f, 0f)));
            //m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.5f, 1f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.5f, 1f, 0.5f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("LaneFriendlySoldierStandByCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.5f, 1f, 0.5f, 0f)));
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
