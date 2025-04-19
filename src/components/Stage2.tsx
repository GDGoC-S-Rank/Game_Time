import "./Stage2.css";
import screenArea from "../resources/images/black.png";
import hsBg from "../resources/images/hs/hbg.png";

// Heart Star
export function Stage2() {
  return (
    <div className="stage2-container">
      <img src={screenArea} alt="screenArea" className="screenArea" />
      <img src={hsBg} alt="hsBg" className="hsBg" />
    </div>
  );
}
