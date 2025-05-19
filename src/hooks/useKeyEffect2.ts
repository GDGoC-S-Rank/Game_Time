import { useEffect } from "react";

// 지속시간이 오래가는 키 이펙트 ✨
export function useKeyEffect2(
  onKeyPress: (key: string) => void,
  onKeyUp: (key: string) => void
) {
  useEffect(() => {
    const handleKeyDown = (event: KeyboardEvent) => {
      if (event.code === "Space" || event.code === "ArrowUp") {
        event.preventDefault(); // 🔴 기본 스크롤 동작 차단
        onKeyPress(event.code); // 눌린 키를 콜백으로 전달
      }
    };

    const handleKeyUp = (event: KeyboardEvent) => {
      onKeyUp(event.code);
    };

    window.addEventListener("keydown", handleKeyDown);
    window.addEventListener("keyup", handleKeyUp);

    return () => {
      window.removeEventListener("keydown", handleKeyDown);
      window.removeEventListener("keyup", handleKeyUp);
    };
  }, [onKeyPress, onKeyUp]);
}
