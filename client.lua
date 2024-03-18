
package.cpath = package.cpath .. ";lib/?.so"
local sox = require("sox");

assert(sox.init())

do
	local s <close> = assert(sox.open_socket())
	
	
end

assert(sox.shutdown())

print("done!")
