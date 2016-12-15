/*
mutilset注意:
当erase(key)时, 是删除值为key的所有元素.
当erase(itertor it)时, 删除一个值为*it的元素.
*/
/*map使用注意:
用map比用 vector + sort + lower_bound慢, 所以如果不是必需, 尽量用后者
使用map[x], 如果x不在map中, 那么x会自动添加到map中, 而使用find()不会.
*/
