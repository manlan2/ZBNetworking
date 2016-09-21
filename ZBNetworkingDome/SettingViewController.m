//
//  SettingViewController.m
//  ZBNetworkingDome
//
//  Created by NQ UEC on 16/8/24.
//  Copyright © 2016年 Suzhibin. All rights reserved.
//

#import "SettingViewController.h"
#import "ZBNetworking.h"
#import "offlineDownloadViewController.h"
typedef void(^SuccessBlock)(id object , NSURLResponse *response);
typedef void(^failBlock)(NSError *error);
@interface SettingViewController ()<UITableViewDelegate,UITableViewDataSource,offlineDelegate>

@property (nonatomic,copy)NSString *path;
@property (nonatomic,strong)UITableView *tableView;
@property (nonatomic,strong)ZBURLSessionManager *manager;
@end

@implementation SettingViewController
- (ZBURLSessionManager *)manager
{
    if (!_manager) {
        _manager = [ZBURLSessionManager manager];
    }
    return _manager;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    //得到沙盒cache文件夹
    NSString *cachePath= [[ZBCacheManager shareCacheManager]getCachesDirectory];
    NSString *Snapshots=@"Snapshots";
    //拼接cache文件夹下的 Snapshots 文件夹
    self.path=[NSString stringWithFormat:@"%@/%@",cachePath,Snapshots];
    
    [self.view addSubview:self.tableView];

}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    return 5;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    static NSString *cellIde=@"cellIde";
    UITableViewCell *cell=[tableView dequeueReusableCellWithIdentifier:cellIde];
    if (!cell) {
        cell=[[UITableViewCell alloc]initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellIde];
    }
    if (indexPath.row==0) {
        cell.textLabel.text=@"清除缓存";
        
        float size=[[ZBCacheManager shareCacheManager]getCacheSize];
        size=size/1000.0/1000.0;
  
        cell.detailTextLabel.text=[NSString stringWithFormat:@"%.2fM",size];

    }
    if (indexPath.row==1) {
        cell.textLabel.text=@"缓存文件数量";
        
        float count=[[ZBCacheManager shareCacheManager]getCacheCount];
        
        cell.detailTextLabel.text= [NSString stringWithFormat:@"%.f",count];
        
    }

    if (indexPath.row==2) {
        cell.textLabel.text=@"清除某个沙盒文件";
    
        float size=[[ZBCacheManager shareCacheManager]getFileSizeWithpath:self.path];

        //fileUnitWithSize 转换单位方法
        cell.detailTextLabel.text=[[ZBCacheManager shareCacheManager] fileUnitWithSize:size];

    }
    if (indexPath.row==3) {
        cell.textLabel.text=@"某个沙盒文件数量";
      
        float count=[[ZBCacheManager shareCacheManager]getFileCountWithpath:self.path];
        
        cell.detailTextLabel.text= [NSString stringWithFormat:@"%.f",count];
        
    }
    
    if (indexPath.row==4) {
        cell.textLabel.text=@"离线下载";
         cell.accessoryType=UITableViewCellAccessoryDisclosureIndicator;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.row==0) {
        
        [[NSURLCache sharedURLCache]removeAllCachedResponses];
        
        //清除缓存
        [[ZBCacheManager shareCacheManager]clearCacheOnOperation:^{
            
            [self.tableView reloadData];
            
        }];
    }
    
    if (indexPath.row==2) {
        
        //清除某个沙盒文件内容
        [[ZBCacheManager shareCacheManager]clearDiskWithpath:self.path operation:^{
            
            [self.tableView reloadData];
            
        }];
    }
    if (indexPath.row==4) {

        offlineDownloadViewController *offlineVC=[[offlineDownloadViewController alloc]init];
        offlineVC.delegate=self;
        [self.navigationController pushViewController:offlineVC animated:YES];
        
    }
    
}
#pragma mark offlineDelegate
- (void)refreshSize
{
    [self.tableView reloadData];
  
}



//懒加载
- (UITableView *)tableView
{
    
    if (!_tableView) {
        _tableView=[[UITableView alloc]initWithFrame:self.view.bounds style:UITableViewStylePlain];
        _tableView.delegate=self;
        _tableView.dataSource=self;
        _tableView.tableFooterView=[[UIView alloc]init];
        
    }
    
    return _tableView;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
