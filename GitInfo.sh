#########################################################################
# File Name: GitInfo.sh
# Author: zhengli
# mail: zldata@aliyun.com
# Created Time: 二  4/ 3 22:56:03 2018
# Brief: 
#########################################################################
#!/bin/bash

# .git/config 				# 相关配置文件

# 查看远程库的详细信息
# git remote show origin

# 推送到远程库
# git push

# 从远程库取回数据，则执行
# git pull




############################################ 分支介绍 ###############################
# 假设github上已经有master分支 和dev分支
# 在本地
# 	git checkout -b dev 		# 新建并切换到本地dev分支
# 	git pull origin dev 		# 本地分支与远程分支相关联
# 在本地新建分支并推送到远程
# 	git checkout -b test
# 	git push origin test   		# 这样远程仓库中也就创建了一个test分支



# 查看分支
# 	git branch 

# 创建本地分支
# 	git branch [dev] 

# 发布dev分支 这样远程仓库也有一个dev分支了
# 发布dev分支指的是同步dev分支的代码到远程服务器
# 	git push origin [dev]:[dev]  

# 在dev分支开发代码 切换到dev分支进行开发
# 	git checkout dev  
#
# 开发代码之后，我们有两个选择
# 第一个：如果功能开发完成了，可以合并主分支
# 	git checkout master 	# 切换到主分支
# 	git merge dev  			# 把dev分支的更改和master合并
# 	git push  				# 提交主分支代码远程
# 	git checkout dev  		# 切换到dev远程分支
# 	git push  				# 提交dev分支到远程
# 第二个：如果功能没有完成，可以直接推送
#	git push  				# 提交到dev远程分支
# 注意：在分支切换之前最好先commit全部的改变，除非你真的知道自己在做什么


# 删除分支
# 	git push origin :dev  	# 删除远程dev分支，危险命令哦
# 下面两条是删除本地分支
#	git checkout master  	# 切换到master分支
#	git branch -d dev  		# 删除本地dev分

#####################################################################################################



###################################### git 查看远程仓库的信息 #######################################
# 1.查看远程仓库的信息
# 可以通过命令 git remote show [remote-name] 查看某个远程仓库的详细信息，比如要看所克隆的 origin 仓库，可以运行：
# 	git remote show origin

# 2.git fetch：相当于是从远程获取最新版本到本地，不会自动merge
# 	Git fetch origin master				# 从远程仓库 抓取master分支，但是不会merge
# 	git log -p master origin/master		# 比较本地master分支与远程master分支的区别
# 	git merge origin/master				# 合并远程分支到本地

# 上述过程其实可以用以下更清晰的方式来进行：
# 	git fetch origin master:tmp	
# 	git diff tmp 
# 	git merge tmp

# 3.git pull：相当于是从远程获取最新版本并merge到本地
# 	git pull origin master
# 	 上述命令其实相当于git fetch 和 git merge
# 	 在实际使用中，git fetch更安全一些
# 	 因为在merge前，我们可以查看更新情况，然后再决定是否合并
#####################################################################################################

