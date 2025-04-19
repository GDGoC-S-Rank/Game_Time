import "./Stage2.css";
import screenBorder from "../resources/images/screenBorder.png";
import heartBg from "../resources/images/hs/hbg.png";
import hfloor from "../resources/images/hs/hfloor.png";

// Heart Star
export function Stage2() {
  return (
    <div className="stage2-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={hfloor} alt="hfloor" className="hfloor" />
      <img src={heartBg} alt="heartBg" className="heartBg" />
    </div>
  );
}
