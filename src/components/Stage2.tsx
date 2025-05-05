import "./Stage2.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";
import heartBg from "../resources/images/hs/hbg.png";
import hfloor from "../resources/images/hs/hfloor.png";
import control_panel from "../resources/images/fontImg/15.png";
import control_1p from "../resources/images/fontImg/cube.png";
import control_2p from "../resources/images/fontImg/exchangeRB.png";
import { useSpaceKeyEffect } from "../hooks/useSpaceKeyEffect";

// Heart Star
export function Stage2() {
  const [isVisible, setIsVisible] = useState(false);

  useSpaceKeyEffect(() => {
    setIsVisible(true);
    setTimeout(() => setIsVisible(false), 300);
  });

  return (
    <div className="stage2-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img src={hfloor} alt="hfloor" className="hfloor" />
      <img src={heartBg} alt="heartBg" className="heartBg" />
      <img src={control_panel} alt="control_panel" className="control_panel" />
      <img
        src={control_1p}
        alt="control_1p"
        className={`control_1p ${isVisible ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="control_2p"
        className={`control_2p ${isVisible ? "visible" : ""}`}
      />
    </div>
  );
}
