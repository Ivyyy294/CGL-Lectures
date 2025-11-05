using GameFramework;

namespace IvyyyAI
{
    public class IvyyyPerception
    {
        public enum ActionTyp
        {
            TurnStart,
            TurnEnd,
            DeployTowers,
            DeploySoldiers
        }

        public Player Player { get; set; }
        public ActionTyp CurrentActionTyp { get; set; }
    }
}
