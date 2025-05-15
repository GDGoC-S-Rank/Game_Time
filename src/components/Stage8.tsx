import "./Stage8.css";
import React, { useState, useEffect } from "react";
import screenBorder from "../resources/images/screenBorder.png";

import bgColor from "../resources/images/fear/bg6.png"; // 배경색
import bgImage1 from "../resources/images/fear/bg6.png"; // 잔디밭
import bgImage2 from "../resources/images/fear/bg5.png"; // 뒤쪽 잔디밭
import bgImage3 from "../resources/images/fear/bg1.png"; // 맨 뒤 나무기둥
import bgImage4 from "../resources/images/fear/bg2.png"; // 청록색 나무
import bgImage5 from "../resources/images/fear/bg3.png"; // 청록색 풀
import bgImage6 from "../resources/images/fear/bg4.png"; // 어두운 나무

import control_panel from "../resources/images/fontImg/07.png";
import control_1p from "../resources/images/fontImg/fear1.png";
import control_2p from "../resources/images/fontImg/fear2.png";
import { useKeyEffect } from "../hooks/useKeyEffect";

// Fear Less!
export function Stage8() {
  const [isVisible_1p, setIsVisible_1p] = useState(false);
  const [isVisible_2p, setIsVisible_2p] = useState(false);

  useKeyEffect((key) => {
    if (key === "Space") {
      setIsVisible_1p(true);
      setTimeout(() => setIsVisible_1p(false), 300);
    } else if (key === "ArrowUp") {
      setIsVisible_2p(true);
      setTimeout(() => setIsVisible_2p(false), 300);
    }
  });

  return (
    <div className="stage8-container">
      <img src={screenBorder} alt="screenBorder" className="screenBorder" />
      <img
        src={control_panel}
        alt="control_panel"
        className="stage8_control_panel"
      />
      <img
        src={control_1p}
        alt="contral_1p"
        className={`stage8_control_1p ${isVisible_1p ? "visible" : ""}`}
      />
      <img
        src={control_2p}
        alt="contral_2p"
        className={`stage8_control_2p ${isVisible_2p ? "visible" : ""}`}
      />
      <img src={bgColor} alt="bgcolor" className="stage8-bgcolor" />
      <img src={bgImage4} alt="bg4" className="stage8-bgImage4" />
      <img src={bgImage5} alt="bg5" className="stage8-bgImage5" />
      <img src={bgImage3} alt="bg3" className="stage8-bgImage3" />
      <img src={bgImage2} alt="bg2" className="stage8-bgImage2" />
      <img src={bgImage6} alt="bg6" className="stage8-bgImage6" />
      <img src={bgImage1} alt="bg1" className="stage8-bgImage1" />
    </div>
  );
}
