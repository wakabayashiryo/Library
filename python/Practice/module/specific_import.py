#特定のメンバだけインポート
from syaku import syaku_to_cm

syaku_to_cm(10)
syaku_to_cm(20)

#asを使用して短縮
import syaku as as_s2cm

as_s2cm.syaku_to_cm(10)
as_s2cm.syaku_to_cm(20)

from syaku import syaku_to_cm as s2cm

s2cm(10)
s2cm(20)
